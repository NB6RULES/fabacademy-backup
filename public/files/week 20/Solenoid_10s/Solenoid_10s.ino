// Solenoid driver for XIAO ESP32-C6
// Hardware:
//   XIAO ESP32-C6 D2  ->  MOSFET gate (with ~10k pull-down to GND recommended)
//   MOSFET drain      ->  solenoid (-)
//   Solenoid (+)      ->  external V+ (12V/24V from your supply)
//   MOSFET source     ->  GND (shared with XIAO GND)
//   Flyback diode across the solenoid coil (cathode to V+, anode to drain).
//
// Behaviour: solenoid ON for 10 s, OFF for 10 s, forever.

#define SOLENOID_PIN D2          // XIAO ESP32-C6 silkscreen D2 -> GPIO2
const unsigned long PERIOD_MS = 10000UL;  // 10 seconds

void setup() {
  Serial.begin(115200);
  pinMode(SOLENOID_PIN, OUTPUT);
  digitalWrite(SOLENOID_PIN, LOW);   // start OFF so it doesn't latch on at boot
  delay(500);
  Serial.println();
  Serial.println("XIAO ESP32-C6 solenoid timer ready.");
  Serial.print("Driving pin D2 (GPIO");
  Serial.print((int)SOLENOID_PIN);
  Serial.println(") HIGH/LOW every 10 s.");
}

void loop() {
  digitalWrite(SOLENOID_PIN, HIGH);
  Serial.println("[ON ] solenoid energised");
  delay(PERIOD_MS);

  digitalWrite(SOLENOID_PIN, LOW);
  Serial.println("[OFF] solenoid released");
  delay(PERIOD_MS);
}
