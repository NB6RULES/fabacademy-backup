// =====================================================================================
//  SMART TOOL BOX  —  Unified firmware for Seeed XIAO ESP32-C6
//  Fuses four previously-standalone sketches into ONE non-blocking program:
//     - DaisyChain_Reader   : polls a 19-node limit-switch / Hall chain (Serial1)
//     - Neopixel_Rainbow     : 299-LED WS2812 strip, travelling rainbow (D0)
//     - RFID_UID_Reader      : RC522 tag reader over SPI
//     - Solenoid driver      : 3 MOSFET-switched drawer locks (D2/D3/D5)
//
//  BEHAVIOUR
//    * Strip runs a travelling rainbow by default.
//    * If a tool is removed from a slot, ONLY that node's LED range blinks red↔off;
//      everything else keeps rainbowing. Indices > 233 never blink (always rainbow).
//    * Tap ANY RFID tag -> all 3 solenoids unlock for 5 s (green flash on the strip),
//      then auto re-lock. (Any tag is valid for now; UID allow-list is a later add.)
//    * Hall nodes 10/18/19 report drawer 1/2/3 open/closed to serial only.
//
//  Everything runs from a single millis() loop — NO blocking delay() in loop() — so the
//  rainbow stays smooth while the chain polls (~170 ms ripple), RFID scans, and the
//  solenoid timer all run together.
//
//  CH32V003 node firmware is UNCHANGED (it auto-derives node_id from chain position).
// =====================================================================================

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <SPI.h>
#include <MFRC522.h>
#include "wifi_manager.h"
#include "firestore_client.h"

// ------------------------------------------------------------------ pin map ----------
#define LED_PIN     D0          // NeoPixel data
#define RST_PIN     D1          // RC522 reset
#define SOL1_PIN    D2          // drawer-1 solenoid (N-ch MOSFET gate)
#define SOL2_PIN    D3          // drawer-2 solenoid
#define SS_PIN      D4          // RC522 SS / CS
#define SOL3_PIN    D5          // drawer-3 solenoid
// D6 / D7 = Serial1 TX / RX to the node chain (set in setup)
#define SCK_PIN     D8          // RC522 SCK
#define MISO_PIN    D9          // RC522 MISO
#define MOSI_PIN    D10         // RC522 MOSI

const uint8_t SOLENOID_PIN[3] = { SOL1_PIN, SOL2_PIN, SOL3_PIN };

// ------------------------------------------------------------------ config -----------
#define NUM_LEDS        299
#define NUM_NODES       19
#define BRIGHTNESS      96      // capped — 299 LEDs all-white would brown out the buck rail

#define POLL_CMD        0xAA
#define POLL_INTERVAL   250     // ms between chain polls (>= chain ripple time)
#define RESPONSE_WAIT   350     // ms to collect a full 19-node reply (~10 ms/node ripple)
#define EXPECTED_BYTES  (1 + NUM_NODES * 2)   // 0xAA + 19*(id,state) = 39

#define UNLOCK_MS       5000    // how long the solenoids stay released after a tag
#define BLINK_MS        250     // red blink half-period (~2 Hz)
#define FRAME_MS        20      // LED frame interval (~50 fps)
#define HUE_STEP        256     // rainbow scroll speed per frame

// Polarity knobs — flip in one line if a slot / magnet is wired the other way.
#define TOOL_PRESENT_PRESSED  1   // button node: tool present == switch pressed == state 1
#define DRAWER_OPEN_STATE     1   // hall node:   drawer OPEN == no magnet == state 1

#define MAX_BLINK_INDEX  233    // hard rule: pixels past this NEVER show the red overlay

// true = Hall drawer-status node (no LEDs); false = button/limit tool node.
// node 10 -> drawer 1, node 18 -> drawer 2, node 19 -> drawer 3.
const bool isHall[NUM_NODES] = {
  false, false, false, false, false,   // nodes 1..5   (tools)
  false, false, false, false, true,    // nodes 6..10  (10 = drawer-1 hall)
  false, false, false, false, false,   // nodes 11..15 (tools)
  false, false, true,  true            // nodes 16..19 (18 = drawer-2, 19 = drawer-3 hall)
};

// Node -> LED segment map (from led_node_index.md). 1-based node ids. Some nodes own
// two segments (5 and 12). Hall nodes 10/18/19 have no segments. All ranges are <= 233,
// so the "no blink past 233" rule is satisfied by construction (and re-checked at render).
struct LedSeg { uint8_t node; uint16_t start; uint16_t end; };
const LedSeg ledSegs[] = {
  { 9,   1,  15 }, { 1,  16,  33 }, { 2,  34,  40 }, { 3,  41,  49 },
  { 5,  50,  55 }, { 4,  56,  94 }, { 5,  95, 100 }, { 6, 101, 107 },
  { 7, 108, 111 }, { 8, 112, 117 },                                   // drawer 1
  {11, 118, 131 }, {12, 132, 146 }, {13, 147, 166 }, {14, 167, 191 },
  {15, 192, 211 }, {16, 212, 217 }, {17, 218, 225 }, {12, 226, 233 }, // drawer 2
};
const uint8_t NUM_SEGS = sizeof(ledSegs) / sizeof(ledSegs[0]);

// ------------------------------------------------------------------ globals ----------
Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
MFRC522 mfrc522(SS_PIN, RST_PIN);

uint8_t  nodeState[NUM_NODES]  = {0};   // last raw byte from each node
bool     toolAbsent[NUM_NODES] = {0};   // computed: button node tool missing?
bool     drawerOpen[3]         = {0};   // drawers 1..3
bool     firstPoll             = true;

uint16_t hueOffset = 0;                 // rainbow animation phase

// chain receive state machine
enum ChainState { CHAIN_IDLE, CHAIN_COLLECTING };
ChainState chainState = CHAIN_IDLE;
uint8_t    rxBuf[64];
uint8_t    rxLen        = 0;
uint32_t   lastPollTime = 0;
uint32_t   pollDeadline = 0;

// lock state
bool     unlocked    = false;
uint32_t unlockStart = 0;

// frame timer
uint32_t lastFrame = 0;

// ------------------------------------------------------------------ helpers ----------
int drawerForNode(uint8_t node_id) {
  if (node_id == 10) return 1;
  if (node_id == 18) return 2;
  if (node_id == 19) return 3;
  return 0;
}

// Which drawer a TOOL node lives in (for Firestore tool docs / events).
// Nodes 1..9 sit in drawer 1, nodes 11..17 in drawer 2 (10/18/19 are Hall sensors).
uint8_t drawerForToolNode(uint8_t node_id) {
  if (node_id >= 1  && node_id <= 9)  return 1;
  if (node_id >= 11 && node_id <= 17) return 2;
  return 0;
}

void setSolenoids(bool on) {
  for (uint8_t i = 0; i < 3; i++) digitalWrite(SOLENOID_PIN[i], on ? HIGH : LOW);
}

void startUnlock(uint32_t now) {
  unlocked    = true;
  unlockStart = now;
  setSolenoids(true);                   // HIGH = coil energised = bolt retracts = UNLOCKED
  Serial.println(F(">>> UNLOCKED — all drawers released for 5 s (green flash)"));
}

// --------------------------------------------------------------- chain poll ----------
void parseChain() {
  if (rxLen == 0) {
    Serial.println(F("[warn] no response from chain — nodes powered / wiring?"));
    return;
  }
  if (rxBuf[0] != POLL_CMD) {
    Serial.printf("[warn] bad framing, first byte = 0x%02X, len=%u\n", rxBuf[0], rxLen);
    return;
  }
  if (rxLen < EXPECTED_BYTES) {
    Serial.printf("[warn] short reply: got %u of %u bytes\n", rxLen, EXPECTED_BYTES);
  }

  for (uint8_t i = 1; i + 1 < rxLen; i += 2) {
    uint8_t node_id = rxBuf[i];
    uint8_t state   = rxBuf[i + 1];
    if (node_id < 1 || node_id > NUM_NODES) continue;

    uint8_t idx     = node_id - 1;
    nodeState[idx]  = state;

    if (isHall[idx]) {
      // drawer open/closed — log only
      int d = drawerForNode(node_id);
      bool nowOpen = (state == DRAWER_OPEN_STATE);
      if (d >= 1 && (firstPoll || nowOpen != drawerOpen[d - 1])) {
        drawerOpen[d - 1] = nowOpen;
        if (!firstPoll) {
          Serial.printf("Drawer %d %s\n", d, nowOpen ? "OPEN" : "CLOSED");
          Cloud::reportDrawer(d, node_id, nowOpen);   // -> events: drawer_open/close
        }
      }
    } else {
      // tool slot — present when pressed, absent (blink red) otherwise
      bool nowAbsent = (state != TOOL_PRESENT_PRESSED);
      if (firstPoll || nowAbsent != toolAbsent[idx]) {
        toolAbsent[idx] = nowAbsent;
        if (!firstPoll)
          Serial.printf("Node %2u  tool %s\n", node_id,
                        nowAbsent ? "REMOVED" : "returned");
        // Sync live presence on every change; also append a taken/returned event,
        // except on the very first poll (boot sync = state only, no fake history).
        Cloud::reportTool(node_id, drawerForToolNode(node_id), !nowAbsent, !firstPoll);
      }
    }
  }
  firstPoll = false;
}

void serviceChain(uint32_t now) {
  switch (chainState) {
    case CHAIN_IDLE:
      if (now - lastPollTime >= POLL_INTERVAL) {
        while (Serial1.available()) Serial1.read();   // drop stale bytes
        Serial1.write((uint8_t)POLL_CMD);
        rxLen        = 0;
        lastPollTime = now;
        pollDeadline = now + RESPONSE_WAIT;
        chainState   = CHAIN_COLLECTING;
      }
      break;

    case CHAIN_COLLECTING:
      while (Serial1.available() && rxLen < sizeof(rxBuf)) {
        rxBuf[rxLen++] = Serial1.read();
      }
      if (rxLen >= EXPECTED_BYTES || now >= pollDeadline) {
        parseChain();
        chainState = CHAIN_IDLE;
      }
      break;
  }
}

// ------------------------------------------------------------------ RFID -------------
void serviceRFID(uint32_t now) {
  if (!mfrc522.PICC_IsNewCardPresent()) return;
  if (!mfrc522.PICC_ReadCardSerial())   return;

  String uid;                           // UPPERCASE colon-hex, matches users.rfidUid
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    char hx[3];
    snprintf(hx, sizeof(hx), "%02X", mfrc522.uid.uidByte[i]);
    uid += hx;
    if (i < mfrc522.uid.size - 1) uid += ':';
  }
  Serial.printf("Tag UID: %s\n", uid.c_str());

  startUnlock(now);                     // any tag is valid for now
  Cloud::reportUnlock(uid);             // -> events: unlock (raw tag)
  mfrc522.PICC_HaltA();
}

// --------------------------------------------------------------- solenoids -----------
void serviceSolenoids(uint32_t now) {
  if (unlocked && (now - unlockStart >= UNLOCK_MS)) {
    unlocked = false;
    setSolenoids(false);                // back to LOW = locked
    Serial.println(F("<<< re-locked"));
  }
}

// ------------------------------------------------------------------ render -----------
void renderStrip(uint32_t now) {
  // ---- base layer ----
  if (unlocked) {
    // green "access granted": bright flash for the first 250 ms, then a gentle breathe.
    uint32_t t  = now - unlockStart;
    uint16_t ph = now % 1600;                                   // 1.6 s breathe period
    uint8_t  g  = (ph < 800) ? map(ph, 0, 800, 60, 255)
                             : map(ph, 800, 1600, 255, 60);
    if (t < 250) g = 255;                                       // opening flash
    uint32_t green = strip.Color(0, g, 0);
    for (uint16_t i = 0; i < NUM_LEDS; i++) strip.setPixelColor(i, green);
  } else {
    // travelling rainbow across the whole strip
    for (uint16_t i = 0; i < NUM_LEDS; i++) {
      uint16_t pixelHue = hueOffset + (uint32_t)i * 65536UL / NUM_LEDS;
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
  }

  // ---- red overlay: absent tools blink red↔off, only for indices <= 233 ----
  bool blinkOn = ((now / BLINK_MS) & 0x01) == 0;
  if (blinkOn) {
    uint32_t red = strip.Color(255, 0, 0);
    for (uint8_t s = 0; s < NUM_SEGS; s++) {
      if (!toolAbsent[ledSegs[s].node - 1]) continue;
      for (uint16_t i = ledSegs[s].start;
           i <= ledSegs[s].end && i <= MAX_BLINK_INDEX && i < NUM_LEDS; i++) {
        strip.setPixelColor(i, red);
      }
    }
  }

  strip.show();
  hueOffset += HUE_STEP;                 // keep the rainbow scrolling even while unlocked
}

// ------------------------------------------------------------------ setup ------------
void setup() {
  Serial.begin(115200);
  uint32_t t0 = millis();
  while (!Serial && (millis() - t0) < 2000) { delay(10); }   // let USB-CDC come up

  // solenoids OFF first so nothing latches on at boot
  for (uint8_t i = 0; i < 3; i++) {
    pinMode(SOLENOID_PIN[i], OUTPUT);
    digitalWrite(SOLENOID_PIN[i], LOW);
  }

  // NeoPixel
  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.show();                          // all off

  // node chain on Serial1 (TX=D6, RX=D7)
  Serial1.begin(115200, SERIAL_8N1, /*RX=*/D7, /*TX=*/D6);

  // RC522 — manual hard reset, then bind SPI to the schematic pins
  pinMode(RST_PIN, OUTPUT);
  digitalWrite(RST_PIN, LOW);  delay(50);
  digitalWrite(RST_PIN, HIGH); delay(100);
  SPI.begin(SCK_PIN, MISO_PIN, MOSI_PIN, SS_PIN);
  SPI.setFrequency(1000000);             // slow + safe on jumper wires
  mfrc522.PCD_Init();
  delay(50);

  Serial.println();
  Serial.println(F("=================================================="));
  Serial.println(F(" SMART TOOL BOX  —  unified firmware up"));
  Serial.println(F("=================================================="));
  byte v = mfrc522.PCD_ReadRegister(MFRC522::VersionReg);
  Serial.printf(" RC522 version: 0x%02X %s\n", v,
                (v == 0x91 || v == 0x92) ? "(good)" : "(check wiring/power)");
  Serial.printf(" %u nodes, %u LEDs. Tap a tag to unlock.\n", NUM_NODES, NUM_LEDS);
  Serial.print(F(" Node types: "));
  for (uint8_t i = 0; i < NUM_NODES; i++)
    Serial.printf("%u=%s ", i + 1, isHall[i] ? "HALL" : "BTN");
  Serial.println();

  // WiFi: join a known network, or fall back to the setup AP for app provisioning.
  WifiManager::begin();
  Serial.printf(" WiFi: %s (%s)\n",
                WifiManager::isProvisioning() ? "PROVISIONING (AP)"
                  : (WifiManager::isOnline() ? "online" : "offline"),
                WifiManager::ip().c_str());

  // Cloud: background task signs in as the device account and pushes state to Firestore.
  Cloud::begin();

  lastPollTime = millis();
}

// ------------------------------------------------------------------ loop -------------
void loop() {
  uint32_t now = millis();

  WifiManager::loop();      // (0) service provisioning AP (no-op once online)
  serviceChain(now);        // (1) poll the 19-node chain, non-blocking
  serviceRFID(now);         // (2) tag -> unlock
  serviceSolenoids(now);    // (3) time-based re-lock

  if (now - lastFrame >= FRAME_MS) {   // (4) rainbow / green base + red overlay
    renderStrip(now);
    lastFrame = now;
  }
}
