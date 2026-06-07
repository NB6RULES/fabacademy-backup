// Host for a 10-node CH32V003 button/Hall daisy-chain.
//
// Board:    Seeed XIAO ESP32-C6
// UART:     Serial1 — TX = D6 (GPIO16), RX = D7 (GPIO17), 115200 8N1
//
// Chain layout (per current build):
//   Nodes 1..9  = button nodes   (state == 1 means PRESSED)
//   Node  10    = Hall sensor    (state == 0 means MAGNET PRESENT)
//
// "Active" means whatever counts as the trigger condition for that node:
//   button -> pressed; Hall -> magnet present.
//
// Protocol (defined by CH32V003 firmware):
//   Host -> chain:  0xAA
//   Chain -> host:  0xAA 0x01 <s1> 0x02 <s2> ... 0x0A <s10>

#include <Arduino.h>

#define POLL_CMD        0xAA
#define NUM_NODES       10
#define POLL_INTERVAL   200
#define RESPONSE_WAIT   180
#define EXPECTED_BYTES  (1 + NUM_NODES * 2)
#define SNAPSHOT_EVERY  10

// true = Hall sensor (active when state == 0)
// false = button     (active when state == 1)
const bool isHall[NUM_NODES] = {
  false, false, false, false, false,   // nodes 1..5  : buttons
  false, false, false, false, true     // nodes 6..10 : buttons, node 10 = Hall
};

uint8_t  rawState[NUM_NODES] = {0};   // last raw byte seen from each node
bool     activePrev[NUM_NODES] = {0}; // last computed "active" flag per node
bool     firstPoll  = true;
uint16_t pollCounter = 0;

static inline bool isActive(uint8_t nodeIdx, uint8_t state) {
  return isHall[nodeIdx] ? (state == 0) : (state == 1);
}

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200, SERIAL_8N1, /*RX=*/D7, /*TX=*/D6);
  delay(500);
  Serial.println();
  Serial.println("XIAO ESP32-C6 mixed chain reader");
  Serial.printf("Polling %u nodes every %u ms on Serial1 (TX=D6, RX=D7)\n",
                NUM_NODES, POLL_INTERVAL);
  Serial.print("Node types: ");
  for (uint8_t i = 0; i < NUM_NODES; i++) {
    Serial.printf("%u=%s ", i + 1, isHall[i] ? "HALL" : "BTN");
  }
  Serial.println();
}

void loop() {
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

  if (len == 0) {
    Serial.println("[warn] no response from chain — check wiring / nodes powered?");
  } else if (buf[0] != POLL_CMD) {
    Serial.printf("[warn] bad framing, first byte = 0x%02X, len=%u\n", buf[0], len);
  } else {
    if (len < EXPECTED_BYTES) {
      Serial.printf("[warn] short response: got %u bytes, expected %u\n",
                    len, EXPECTED_BYTES);
    }

    for (uint8_t i = 1; i + 1 < len; i += 2) {
      uint8_t node_id = buf[i];
      uint8_t state   = buf[i + 1];

      if (node_id < 1 || node_id > NUM_NODES) continue;
      uint8_t idx  = node_id - 1;
      rawState[idx] = state;
      bool nowActive  = isActive(idx, state);
      bool wasActive  = activePrev[idx];
      activePrev[idx] = nowActive;

      if (!firstPoll && nowActive != wasActive) {
        if (nowActive) {
          Serial.printf("Node %2u  ACTIVE   (%s)\n",
                        node_id, isHall[idx] ? "magnet present" : "button pressed");
        } else {
          Serial.printf("Node %2u  inactive (%s)\n",
                        node_id, isHall[idx] ? "magnet removed" : "button released");
        }
      }
    }
    firstPoll = false;

    if ((pollCounter % SNAPSHOT_EVERY) == 0) {
      // List of currently active node IDs — quick visual of who's triggered.
      Serial.print("[snapshot] ACTIVE: ");
      uint8_t activeCount = 0;
      for (uint8_t n = 0; n < NUM_NODES; n++) {
        if (activePrev[n]) {
          Serial.printf("%u%s ", n + 1, isHall[n] ? "(H)" : "");
          activeCount++;
        }
      }
      if (activeCount == 0) Serial.print("(none)");
      Serial.println();
    }
  }

  pollCounter++;
  delay(POLL_INTERVAL);
}
