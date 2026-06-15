// =====================================================================
//  Full integrated system for the XIAO ESP32-C6
// ---------------------------------------------------------------------
//  Behaviour:
//    Idle state:
//      - Polls the 10-node CH32V003 daisy-chain at 5 Hz.
//      - Prints "ACTIVE" state changes for buttons (nodes 1..9) and the
//        Hall sensor (node 10) as they happen.
//      - Solenoid OFF, NeoPixel strip OFF.
//      - Waits for an RFID tag.
//
//    On RFID tag detected:
//      - Prints the UID.
//      - Turns the solenoid ON for 10 seconds.
//      - During those 10 seconds, the strip is gated by the Hall sensor:
//          magnet PRESENT  -> strip OFF
//          magnet ABSENT   -> strip ON (animated rainbow crawl)
//      - Continues polling and printing button activity throughout.
//      - After 10 s: solenoid OFF, strip OFF, returns to idle.
//
//  Pin map (all on XIAO ESP32-C6 silkscreen):
//      D0  -> NeoPixel DIN
//      D1  -> RFID RST
//      D2  -> Solenoid MOSFET gate
//      D4  -> RFID SS / CS
//      D6  -> Serial1 TX -> Node 1 DIN (chain)
//      D7  -> Serial1 RX <- Node 10 DOUT (chain)
//      D8  -> SPI SCK   (RFID)
//      D9  -> SPI MISO  (RFID)
//      D10 -> SPI MOSI  (RFID)
//      GND shared with chain GND and RFID GND.
// =====================================================================

#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Adafruit_NeoPixel.h>

// ---- NeoPixel ----
#define LED_PIN        D0
#define NUM_LEDS       117
#define BRIGHTNESS     128
Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
uint16_t hueOffset = 0;

// ---- Solenoid ----
#define SOLENOID_PIN   D2

// ---- RFID ----
#define RFID_RST   D1
#define RFID_SS    D4
#define SPI_SCK    D8
#define SPI_MISO   D9
#define SPI_MOSI   D10
MFRC522 mfrc522(RFID_SS, RFID_RST);

// ---- Chain ----
#define POLL_CMD        0xAA
#define NUM_NODES       10
#define POLL_INTERVAL   200
#define RESPONSE_WAIT   180
#define EXPECTED_BYTES  (1 + NUM_NODES * 2)
#define SNAPSHOT_EVERY  10
#define HALL_NODE_IDX   9         // node 10 (1-based) = index 9
// If your node 10 reports state==1 for "magnet present" (because it's
// still running button firmware, or the sensor is wired the other way),
// flip this to true. Default = false = "0 means magnet present".
#define HALL_INVERT     false

const bool isHall[NUM_NODES] = {
  false, false, false, false, false,
  false, false, false, false, true
};

// Hall raw default = 1 (no magnet), so if the chain never updates we
// fall through to "rainbow on" instead of "stay off forever".
uint8_t  rawState[NUM_NODES] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
bool     activePrev[NUM_NODES] = {0};
bool     firstChainPoll  = true;
uint16_t pollCounter = 0;
uint32_t lastChainPoll = 0;

// ---- Session (RFID-triggered 10s window) ----
bool     inSession      = false;
uint32_t sessionEndTime = 0;
uint32_t lastHallReport = 0;
const uint32_t SESSION_DURATION_MS = 10000;
const uint32_t HALL_REPORT_INTERVAL = 500;   // ms between Hall debug prints

static inline bool isMagnetPresent(uint8_t raw) {
  // Default: 0 = magnet present. HALL_INVERT flips that.
  return HALL_INVERT ? (raw == 1) : (raw == 0);
}

// ---- RFID polling ----
uint32_t lastRfidCheck = 0;
const uint32_t RFID_CHECK_INTERVAL = 80;   // ms between RFID polls

// ---- NeoPixel animation ----
bool     stripActive = false;
uint32_t lastFrame   = 0;
const uint32_t FRAME_INTERVAL = 25;        // ms per rainbow frame

static inline bool isNodeActive(uint8_t idx, uint8_t state) {
  return isHall[idx] ? (state == 0) : (state == 1);
}

void setStripOff() {
  strip.clear();
  strip.show();
  stripActive = false;
}

void setStripRainbowFrame() {
  for (uint16_t i = 0; i < NUM_LEDS; i++) {
    uint16_t pixelHue = hueOffset + (i * 65536UL / NUM_LEDS);
    strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
  }
  strip.show();
  hueOffset += 512;
}

void pollChain() {
  while (Serial1.available()) Serial1.read();
  Serial1.write((uint8_t)POLL_CMD);

  uint32_t deadline = millis() + RESPONSE_WAIT;
  uint8_t  buf[64];
  uint8_t  len = 0;
  while (millis() < deadline && len < sizeof(buf)) {
    if (Serial1.available()) {
      buf[len++] = Serial1.read();
      if (len >= EXPECTED_BYTES) break;
    }
  }

  if (len == 0 || buf[0] != POLL_CMD) {
    // chain silent / mis-framed — quiet here, snapshot will show nothing
    return;
  }

  // Rate-limited raw dump so we can debug what each node is actually saying.
  // Prints once every 20 polls (~4 s).
  static uint16_t dumpCounter = 0;
  if ((dumpCounter++ % 20) == 0) {
    Serial.printf("[raw] %u bytes:", len);
    for (uint8_t k = 0; k < len; k++) Serial.printf(" %02X", buf[k]);
    Serial.println();
  }

  for (uint8_t i = 1; i + 1 < len; i += 2) {
    uint8_t node_id = buf[i];
    uint8_t state   = buf[i + 1];
    if (node_id < 1 || node_id > NUM_NODES) continue;
    uint8_t idx  = node_id - 1;
    rawState[idx] = state;
    bool nowActive  = isNodeActive(idx, state);
    bool wasActive  = activePrev[idx];
    activePrev[idx] = nowActive;

    if (!firstChainPoll && nowActive != wasActive) {
      if (nowActive) {
        Serial.printf("Node %2u  ACTIVE   (%s)\n",
                      node_id, isHall[idx] ? "magnet present" : "button pressed");
      } else {
        Serial.printf("Node %2u  inactive (%s)\n",
                      node_id, isHall[idx] ? "magnet removed" : "button released");
      }
    }
  }
  firstChainPoll = false;

  if ((pollCounter % SNAPSHOT_EVERY) == 0) {
    Serial.print("[snapshot] ACTIVE: ");
    uint8_t count = 0;
    for (uint8_t n = 0; n < NUM_NODES; n++) {
      if (activePrev[n]) {
        Serial.printf("%u%s ", n + 1, isHall[n] ? "(H)" : "");
        count++;
      }
    }
    if (count == 0) Serial.print("(none)");
    Serial.println();
  }
  pollCounter++;
}

void checkRfid() {
  if (!mfrc522.PICC_IsNewCardPresent()) return;
  if (!mfrc522.PICC_ReadCardSerial())   return;

  Serial.print("RFID tag UID: ");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (mfrc522.uid.uidByte[i] < 0x10) Serial.print('0');
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    if (i < mfrc522.uid.size - 1) Serial.print(':');
  }
  Serial.println();

  mfrc522.PICC_HaltA();

  // Start the 10-second session.
  inSession      = true;
  sessionEndTime = millis() + SESSION_DURATION_MS;
  digitalWrite(SOLENOID_PIN, HIGH);
  Serial.println(">>> SESSION START: solenoid ON for 10 s, strip gated by Hall sensor.");

  // Force a solid RED flash on the strip for ~400 ms to prove the strip
  // output path is alive in this integrated build. If you see a red flash,
  // the rainbow path works too. If you see nothing, strip output is broken.
  Serial.println("    [diag] forcing red flash on strip...");
  for (uint16_t i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, strip.Color(255, 0, 0));
  }
  strip.show();
  delay(400);
  strip.clear();
  strip.show();
  stripActive = false;
  lastFrame   = 0;
  Serial.println("    [diag] red flash done.");
  Serial.printf("    Initial Hall raw state (node 10) = %u  (%s)\n",
                rawState[HALL_NODE_IDX],
                isMagnetPresent(rawState[HALL_NODE_IDX])
                  ? "magnet PRESENT - strip will stay off"
                  : "no magnet - strip will rainbow");
  lastHallReport = 0;   // make sure we print Hall status immediately
}

void endSession() {
  inSession = false;
  digitalWrite(SOLENOID_PIN, LOW);
  setStripOff();
  Serial.println("<<< SESSION END: solenoid OFF, strip OFF.");
}

void setup() {
  Serial.begin(115200);
  uint32_t t0 = millis();
  while (!Serial && (millis() - t0) < 2000) { delay(10); }

  // Solenoid
  pinMode(SOLENOID_PIN, OUTPUT);
  digitalWrite(SOLENOID_PIN, LOW);

  // Chain UART
  Serial1.begin(115200, SERIAL_8N1, /*RX=*/D7, /*TX=*/D6);

  // NeoPixel
  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.clear();
  strip.show();

  // RFID
  pinMode(RFID_RST, OUTPUT);
  digitalWrite(RFID_RST, LOW);  delay(50);
  digitalWrite(RFID_RST, HIGH); delay(100);
  SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI, RFID_SS);
  SPI.setFrequency(1000000);
  mfrc522.PCD_Init();
  delay(50);

  Serial.println();
  Serial.println("================================================");
  Serial.println(" XIAO ESP32-C6 full integrated system online");
  Serial.println(" Tap an RFID tag to start a 10-second session.");
  Serial.println("================================================");
  Serial.print("Node types: ");
  for (uint8_t i = 0; i < NUM_NODES; i++) {
    Serial.printf("%u=%s ", i + 1, isHall[i] ? "HALL" : "BTN");
  }
  Serial.println();
}

void loop() {
  uint32_t now = millis();

  // 1. Chain poll
  if (now - lastChainPoll >= POLL_INTERVAL) {
    lastChainPoll = now;
    pollChain();
  }

  // 2. RFID polling — only when not already in a session
  if (!inSession && (now - lastRfidCheck) >= RFID_CHECK_INTERVAL) {
    lastRfidCheck = now;
    checkRfid();
  }

  // 3. Session lifecycle
  if (inSession) {
    if ((int32_t)(now - sessionEndTime) >= 0) {
      endSession();
    } else {
      // Per-second debug print of what we think the Hall sensor is saying.
      if (now - lastHallReport >= HALL_REPORT_INTERVAL) {
        lastHallReport = now;
        Serial.printf("[hall] rawState[10]=%u  decision: %s\n",
                      rawState[HALL_NODE_IDX],
                      isMagnetPresent(rawState[HALL_NODE_IDX]) ? "MAGNET PRESENT (strip off)"
                                                               : "no magnet (strip rainbow)");
      }

      bool magnetPresent = isMagnetPresent(rawState[HALL_NODE_IDX]);
      if (magnetPresent) {
        if (stripActive) {
          Serial.printf("[session] magnet present (Hall=0) -> strip OFF\n");
          setStripOff();
        }
      } else {
        // Magnet absent -> animate rainbow.
        if (!stripActive) {
          Serial.printf("[session] no magnet (Hall=%u) -> strip ON (rainbow)\n",
                        rawState[HALL_NODE_IDX]);
          stripActive = true;
          lastFrame = 0;  // force immediate first frame
        }
        if (now - lastFrame >= FRAME_INTERVAL) {
          lastFrame = now;
          setStripRainbowFrame();
        }
      }
    }
  }
}
