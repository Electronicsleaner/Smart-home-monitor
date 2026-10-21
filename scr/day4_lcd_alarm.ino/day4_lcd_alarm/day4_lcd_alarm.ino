// Day 4: I2C LCD, buzzer and LED indicators driven by DHT22 temperature
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHT_PIN     2
#define DHT_TYPE    DHT22
#define BUZZER_PIN  8
#define LED_GREEN   9
#define LED_RED     10

#define TEMP_HIGH   35.0   // alarm threshold in degrees C

DHT dht(DHT_PIN, DHT_TYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ---------- Output functions ----------
void showNormal() {
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_RED, LOW);
  noTone(BUZZER_PIN);
}

void showAlarm() {
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, HIGH);
  tone(BUZZER_PIN, 1000);        // 1 kHz beep
}

void showOnLcd(float temp, float hum, bool alarm) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temp, 1);
  lcd.print("C H:");
  lcd.print(hum, 0);
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print(alarm ? "ALARM: HIGH TEMP" : "Status: Normal");
}

// ---------- Main ----------
void setup() {
  Serial.begin(9600);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  dht.begin();
  lcd.init();
  lcd.backlight();
}

void loop() {
  float temp = dht.readTemperature();
  float hum  = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    Serial.println("DHT22 read error");
    noTone(BUZZER_PIN);
    lcd.clear();
    lcd.print("Sensor error");
    delay(2000);
    return;
  }

  bool alarm = (temp > TEMP_HIGH);

  if (alarm) showAlarm();
  else       showNormal();

  showOnLcd(temp, hum, alarm);

  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" C  Humidity: ");
  Serial.print(hum);
  Serial.print(" %  Alarm: ");
  Serial.println(alarm ? "ON" : "OFF");

  delay(2000);   // DHT22 needs about 2 s between reads
}
