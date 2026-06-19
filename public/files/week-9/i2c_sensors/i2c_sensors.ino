// ATtiny1624 - read APDS-9960 (gesture/proximity/color/ALS) and VL53L0X (distance)
// over I2C and print results over Serial.
//
// Board: megaTinyCore, "ATtiny1624" (atxy4), default I2C pins: SDA=PB1, SCL=PB0
// Libraries: "SparkFun APDS9960 RGB and Gesture Sensor", "VL53L0X" (Pololu)

#include <Wire.h>
#include <SparkFun_APDS9960.h>
#include <VL53L0X.h>

SparkFun_APDS9960 apds = SparkFun_APDS9960();
VL53L0X tof;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  pinMode(PIN_PA3, OUTPUT); // heartbeat LED

  Serial.println(F("Initializing sensors..."));

  if (apds.init()) {
    Serial.println(F("APDS-9960 init OK"));
  } else {
    Serial.println(F("APDS-9960 init FAILED"));
  }
  apds.enableLightSensor(false);
  apds.enableProximitySensor(false);
  apds.enableGestureSensor(false);

  tof.setTimeout(500);
  if (tof.init()) {
    Serial.println(F("VL53L0X init OK"));
  } else {
    Serial.println(F("VL53L0X init FAILED"));
  }
}

void loop() {
  digitalWrite(PIN_PA3, !digitalRead(PIN_PA3));

  uint16_t ambient, red, green, blue;
  if (apds.readAmbientLight(ambient) && apds.readRedLight(red) &&
      apds.readGreenLight(green) && apds.readBlueLight(blue)) {
    Serial.print(F("ALS:"));
    Serial.print(ambient);
    Serial.print(F(" R:"));
    Serial.print(red);
    Serial.print(F(" G:"));
    Serial.print(green);
    Serial.print(F(" B:"));
    Serial.println(blue);
  }

  uint8_t proximity;
  if (apds.readProximity(proximity)) {
    Serial.print(F("Proximity:"));
    Serial.println(proximity);
  }

  if (apds.isGestureAvailable()) {
    switch (apds.readGesture()) {
      case DIR_UP:    Serial.println(F("Gesture: UP"));    break;
      case DIR_DOWN:  Serial.println(F("Gesture: DOWN"));  break;
      case DIR_LEFT:  Serial.println(F("Gesture: LEFT"));  break;
      case DIR_RIGHT: Serial.println(F("Gesture: RIGHT")); break;
      case DIR_NEAR:  Serial.println(F("Gesture: NEAR"));  break;
      case DIR_FAR:   Serial.println(F("Gesture: FAR"));   break;
      default: break;
    }
  }

  uint16_t distance = tof.readRangeSingleMillimeters();
  if (tof.timeoutOccurred()) {
    Serial.println(F("VL53L0X: TIMEOUT"));
  } else {
    Serial.print(F("Distance:"));
    Serial.print(distance);
    Serial.println(F("mm"));
  }

  Serial.println(F("------"));
  delay(300);
}
