// =============================================================
//  RFID UID reader for Seeed Studio XIAO (ESP32-S3 or ESP32-C6)
//  Prints the UID of any MIFARE / RC522 tag to the Serial Monitor
// -------------------------------------------------------------
//  Wiring (matches your schematic):
//      RC522  3.3V  -> XIAO  3V3
//      RC522  GND   -> XIAO  GND
//      RC522  RST   -> XIAO  D1
//      RC522  SDA   -> XIAO  D4   (this is SS / CS for SPI)
//      RC522  SCK   -> XIAO  D8
//      RC522  MISO  -> XIAO  D9
//      RC522  MOSI  -> XIAO  D10
//      RC522  IRQ   -> leave unconnected
//
//  IMPORTANT: power the RC522 from 3V3, NEVER from 5V.
// =============================================================

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN   D1
#define SS_PIN    D4
#define SCK_PIN   D8
#define MISO_PIN  D9
#define MOSI_PIN  D10

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(115200);
  // Wait a bit for the USB serial to come up (XIAO uses native USB-CDC)
  unsigned long t0 = millis();
  while (!Serial && (millis() - t0) < 3000) { delay(10); }

  // Manual hard reset of the RC522 before SPI talks to it.
  // Some boards / modules need this — the library's auto-reset can race the boot.
  pinMode(RST_PIN, OUTPUT);
  digitalWrite(RST_PIN, LOW);
  delay(50);
  digitalWrite(RST_PIN, HIGH);
  delay(100);

  // Bind SPI to the pins on the schematic
  SPI.begin(SCK_PIN, MISO_PIN, MOSI_PIN, SS_PIN);
  // Slow the SPI clock down to 1 MHz — way under spec, but rules out signal-integrity issues
  // on long jumper wires / breadboards. RC522 supports up to 10 MHz.
  SPI.setFrequency(1000000);

  mfrc522.PCD_Init();
  delay(50);

  Serial.println();
  Serial.println(F("=========================================="));
  Serial.println(F(" RFID reader starting up..."));
  Serial.println(F("=========================================="));

  // Read the version 5 times. If it's wiring, the value will be 0x00 or 0xFF every time.
  // If it's intermittent (signal integrity), values will vary.
  for (int i = 0; i < 5; i++) {
    byte v = mfrc522.PCD_ReadRegister(MFRC522::VersionReg);
    Serial.print(F("RC522 firmware version read #"));
    Serial.print(i + 1);
    Serial.print(F(": 0x"));
    if (v < 0x10) Serial.print(F("0"));
    Serial.print(v, HEX);
    if (v == 0x91) Serial.println(F("  -> v1.0 (good)"));
    else if (v == 0x92) Serial.println(F("  -> v2.0 (good)"));
    else if (v == 0x88) Serial.println(F("  -> clone (good)"));
    else if (v == 0x00) Serial.println(F("  -> NO RESPONSE (likely SS/SCK/MOSI not connected, or RC522 unpowered)"));
    else if (v == 0xFF) Serial.println(F("  -> BUS IDLE (likely MISO not connected, RC522 unpowered, or in reset)"));
    else                 Serial.println(F("  -> unknown but non-error"));
    delay(150);
  }

  Serial.println();
  Serial.println(F("If you see 0xFF five times in a row:"));
  Serial.println(F("  1. Is the small LED on the RC522 board lit? If NO, fix 3V3 + GND first."));
  Serial.println(F("  2. Try swapping MISO (D9) and MOSI (D10). Mixing them up is the #1 mistake."));
  Serial.println(F("  3. Make sure SDA (D4) is firmly seated — it's chip select."));
  Serial.println(F("  4. Confirm RST (D1) jumper is in."));
  Serial.println();
  Serial.println(F(" Tap a tag on the RC522 to read its UID."));
}

void loop() {
  // Bail out early if there's nothing new to read
  if (!mfrc522.PICC_IsNewCardPresent()) return;
  if (!mfrc522.PICC_ReadCardSerial())    return;

  // Print UID as colon-separated hex, e.g. "DE:AD:BE:EF"
  Serial.print(F("Tag UID: "));
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (mfrc522.uid.uidByte[i] < 0x10) Serial.print(F("0"));
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    if (i < mfrc522.uid.size - 1) Serial.print(F(":"));
  }
  Serial.print(F("   (size="));
  Serial.print(mfrc522.uid.size);
  Serial.println(F(" bytes)"));

  // Stop talking to this card so the same tag doesn't spam the monitor
  mfrc522.PICC_HaltA();
  delay(400);
}
