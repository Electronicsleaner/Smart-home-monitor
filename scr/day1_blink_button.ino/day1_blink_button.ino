// Day 1: LED controlled by a push button (INPUT_PULLUP) with Serial debugging
#define LED_PIN 13
#define BUTTON_PIN 2

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);   // internal pull-up: HIGH when released
}

void loop() {
  int state = digitalRead(BUTTON_PIN);
  Serial.println(state);

  if (state == LOW) {                  // LOW means pressed
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
  delay(100);
}
