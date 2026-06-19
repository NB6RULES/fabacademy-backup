// ATtiny1624 - visual I2C presence check, no Serial wiring needed.
// LED on PA3 blinks a count for each sensor found, then pauses.
//   2 blinks = VL53L0X (0x29) ACKed
//   3 blinks = APDS-9960 (0x39) ACKed
//   1 long blink = neither sensor responded
//
// I2C pins (megaTinyCore default for ATtiny1624): SDA=PB1, SCL=PB0

#include <Wire.h>

const uint8_t LED = PIN_PA3;
const uint8_t ADDR_VL53L0X = 0x29;
const uint8_t ADDR_APDS9960 = 0x39;

void blinkTimes(uint8_t n) {
  for (uint8_t i = 0; i < n; i++) {
    digitalWrite(LED, HIGH);
    delay(150);
    digitalWrite(LED, LOW);
    delay(150);
  }
}

bool i2cPing(uint8_t addr) {
  Wire.beginTransmission(addr);
  return Wire.endTransmission() == 0;
}

void setup() {
  pinMode(LED, OUTPUT);
  Wire.begin();
}

void loop() {
  bool tofFound = i2cPing(ADDR_VL53L0X);
  bool apdsFound = i2cPing(ADDR_APDS9960);

  if (tofFound) blinkTimes(2);
  delay(400);
  if (apdsFound) blinkTimes(3);

  if (!tofFound && !apdsFound) {
    digitalWrite(LED, HIGH);
    delay(1000);
    digitalWrite(LED, LOW);
  }

  delay(1500);
}
