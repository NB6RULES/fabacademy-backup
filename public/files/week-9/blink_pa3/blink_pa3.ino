// ATtiny1624 - blink LED on PA3
// Board: megaTinyCore, select "ATtiny1624"
// PA3 = Arduino pin "PIN_PA3"

void setup() {
  pinMode(PIN_PA3, OUTPUT);
}

void loop() {
  digitalWrite(PIN_PA3, HIGH);
  delay(500);
  digitalWrite(PIN_PA3, LOW);
  delay(500);
}
