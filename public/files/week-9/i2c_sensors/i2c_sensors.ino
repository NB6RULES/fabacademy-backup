// ATtiny1624 - read APDS-9960 (gesture/proximity/color/ALS), VL53L0X (distance),
// and RCWL-0516 (microwave motion) and print results over Serial.
//
// Board: megaTinyCore, "ATtiny1624" (atxy4), default I2C pins: SDA=PB1, SCL=PB0
// Serial1 (USB/debug) pins: TX=PA1, RX=PA2
// RCWL-0516 OUT pin: PA4 (digital, HIGH while motion detected)
// Libraries: "SparkFun APDS9960 RGB and Gesture Sensor", "VL53L0X" (Pololu)

#include <Wire.h>
#include <SparkFun_APDS9960.h>
#include <VL53L0X.h>

const uint8_t RCWL_PIN = PIN_PA4;

SparkFun_APDS9960 apds = SparkFun_APDS9960();
VL53L0X tof;
bool apdsReady = false;

void setup() {
  Serial1.begin(115200);
  Wire.begin();

  pinMode(PIN_PA3, OUTPUT); // heartbeat LED
  pinMode(RCWL_PIN, INPUT);

  Serial1.println(F("Initializing sensors..."));

  apdsReady = apds.init();
  if (apdsReady) {
    Serial1.println(F("APDS-9960 init OK"));
    apds.enableLightSensor(false);
    apds.enableProximitySensor(false);
    apds.enableGestureSensor(false);
  } else {
    Serial1.println(F("APDS-9960 init FAILED - skipping APDS reads"));
  }

  tof.setTimeout(500);
  if (tof.init()) {
    Serial1.println(F("VL53L0X init OK"));
  } else {
    Serial1.println(F("VL53L0X init FAILED"));
  }
}

void loop() {
  digitalWrite(PIN_PA3, !digitalRead(PIN_PA3));

  if (apdsReady) {
    uint16_t ambient, red, green, blue;
    if (apds.readAmbientLight(ambient) && apds.readRedLight(red) &&
        apds.readGreenLight(green) && apds.readBlueLight(blue)) {
      Serial1.print(F("ALS:"));
      Serial1.print(ambient);
      Serial1.print(F(" R:"));
      Serial1.print(red);
      Serial1.print(F(" G:"));
      Serial1.print(green);
      Serial1.print(F(" B:"));
      Serial1.println(blue);
    }

    uint8_t proximity;
    if (apds.readProximity(proximity)) {
      Serial1.print(F("Proximity:"));
      Serial1.println(proximity);
    }

    if (apds.isGestureAvailable()) {
      switch (apds.readGesture()) {
        case DIR_UP:    Serial1.println(F("Gesture: UP"));    break;
        case DIR_DOWN:  Serial1.println(F("Gesture: DOWN"));  break;
        case DIR_LEFT:  Serial1.println(F("Gesture: LEFT"));  break;
        case DIR_RIGHT: Serial1.println(F("Gesture: RIGHT")); break;
        case DIR_NEAR:  Serial1.println(F("Gesture: NEAR"));  break;
        case DIR_FAR:   Serial1.println(F("Gesture: FAR"));   break;
        default: break;
      }
    }
  }

  uint16_t distance = tof.readRangeSingleMillimeters();
  if (tof.timeoutOccurred()) {
    Serial1.println(F("VL53L0X: TIMEOUT"));
  } else {
    Serial1.print(F("Distance:"));
    Serial1.print(distance);
    Serial1.println(F("mm"));
  }

  Serial1.print(F("Motion:"));
  Serial1.println(digitalRead(RCWL_PIN) ? F("DETECTED") : F("clear"));

  Serial1.println(F("------"));
  delay(300);
}
