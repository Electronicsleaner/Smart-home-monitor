// Day 2: Potentiometer controls LED brightness (PWM), LDR light reading
#define LED_PIN 9      // PWM pin (marked ~)
#define POT_PIN A0
#define LDR_PIN A1

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  int potValue = analogRead(POT_PIN);                // 0-1023 (10-bit ADC)
  int brightness = map(potValue, 0, 1023, 0, 255);   // PWM range
  int light = analogRead(LDR_PIN);                   // 0-1023

  analogWrite(LED_PIN, brightness);

  Serial.print("Pot: ");
  Serial.print(potValue);
  Serial.print("  Brightness: ");
  Serial.print(brightness);
  Serial.print("  Light: ");
  Serial.println(light);

  delay(200);
}
