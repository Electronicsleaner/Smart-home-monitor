// Day 3: DHT22 (temperature, humidity) and HC-SR04 (distance)
#include <DHT.h>

#define DHT_PIN   2
#define DHT_TYPE  DHT22
#define TRIG_PIN  3
#define ECHO_PIN  4

DHT dht(DHT_PIN, DHT_TYPE);

// ---------- Sensor functions ----------
float readTemperature() {
  return dht.readTemperature();   // degrees C
}

float readHumidity() {
  return dht.readHumidity();      // % RH
}

float readDistanceCm() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);   // 10 us trigger pulse
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000); // timeout 30 ms
  if (duration == 0) return -1;   // nothing detected
  return duration * 0.0343 / 2;   // speed of sound, round trip
}

// ---------- Main ----------
void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  dht.begin();
}

void loop() {
  float temp = readTemperature();
  float hum  = readHumidity();
  float dist = readDistanceCm();

  if (isnan(temp) || isnan(hum)) {
    Serial.println("DHT22 read error");
  } else {
    Serial.print("Temp: ");
    Serial.print(temp);
    Serial.print(" C  Humidity: ");
    Serial.print(hum);
    Serial.print(" %  ");
  }

  Serial.print("Distance: ");
  if (dist < 0) Serial.println("out of range");
  else { Serial.print(dist); Serial.println(" cm"); }

  delay(2000);   // DHT22 needs about 2 s between reads
}
