// Smart Home Environment Monitoring System (final project)
// Arduino Uno: DHT22, HC-SR04, LDR, PIR, I2C LCD, LEDs, buzzer, Serial log
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// ---------- Pins ----------
#define DHT_PIN     2
#define DHT_TYPE    DHT22
#define TRIG_PIN    3
#define ECHO_PIN    4
#define PIR_PIN     5
#define BUZZER_PIN  8
#define LED_GREEN   9
#define LED_RED     10
#define LDR_PIN     A0

// ---------- Alarm thresholds (calibrated in Wokwi) ----------
#define TEMP_HIGH        35.0   // deg C
#define DIST_LOW         10.0   // cm
#define DARK_THRESHOLD   600    // ADC value
#define DARK_IF_LOW      false  // Wokwi LDR module: dark gives a HIGH reading

DHT dht(DHT_PIN, DHT_TYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

int page = 0;   // LCD page toggle

// ---------- Sensor functions ----------
float readDistanceCm() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  if (duration == 0) return -1;
  return duration * 0.0343 / 2;
}

int readLight()   { return analogRead(LDR_PIN); }
bool readMotion() { return digitalRead(PIR_PIN) == HIGH; }

bool isDark(int v) {
  return DARK_IF_LOW ? (v < DARK_THRESHOLD) : (v > DARK_THRESHOLD);
}

// ---------- Alarm logic ----------
// Returns a short reason string, or "" if everything is normal
const char* checkAlarm(float temp, float dist, int light) {
  if (temp > TEMP_HIGH)              return "HIGH TEMP";
  if (dist >= 0 && dist < DIST_LOW)  return "TOO CLOSE";
  if (isDark(light))                 return "TOO DARK";
  return "";
}

// ---------- Output functions ----------
void setIndicators(bool alarm) {
  digitalWrite(LED_GREEN, alarm ? LOW : HIGH);
  digitalWrite(LED_RED,   alarm ? HIGH : LOW);
  if (alarm) tone(BUZZER_PIN, 1000);
  else       noTone(BUZZER_PIN);
}

void showLcd(float temp, float hum, float dist, int light, bool motion, const char* reason) {
  lcd.clear();
  if (page == 0) {
    lcd.setCursor(0, 0);
    lcd.print("T:");  lcd.print(temp, 1);
    lcd.print("C H:"); lcd.print(hum, 0); lcd.print("%");
    lcd.setCursor(0, 1);
    if (reason[0] == '\0') lcd.print("Status: Normal");
    else { lcd.print("ALARM:"); lcd.print(reason); }
  } else {
    lcd.setCursor(0, 0);
    lcd.print("L:"); lcd.print(light);
    lcd.print(" D:");
    if (dist < 0) lcd.print("--");
    else          lcd.print(dist, 0);
    lcd.print("cm");
    lcd.setCursor(0, 1);
    lcd.print("Motion: ");
    lcd.print(motion ? "YES" : "NO");
  }
  page = 1 - page;   // switch page for next cycle
}

void logSerial(float temp, float hum, float dist, int light, bool motion, const char* reason) {
  Serial.print("T=");      Serial.print(temp, 1);
  Serial.print(",H=");     Serial.print(hum, 0);
  Serial.print(",Light="); Serial.print(light);
  Serial.print(",Dist=");  Serial.print(dist, 1);
  Serial.print(",Motion=");Serial.print(motion ? 1 : 0);
  Serial.print(",Alarm="); Serial.println(reason[0] == '\0' ? "NONE" : reason);
}

// ---------- Main ----------
void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(PIR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.print("Smart Home");
  lcd.setCursor(0, 1);
  lcd.print("Monitor Ready");
  delay(2000);
}

void loop() {
  float temp = dht.readTemperature();
  float hum  = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    Serial.println("DHT22 read error");
    noTone(BUZZER_PIN);
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, LOW);
    lcd.clear();
    lcd.print("Sensor error");
    delay(2000);
    return;
  }

  float dist   = readDistanceCm();
  int   light  = readLight();
  bool  motion = readMotion();

  const char* reason = checkAlarm(temp, dist, light);
  bool alarm = (reason[0] != '\0');

  setIndicators(alarm);
  showLcd(temp, hum, dist, light, motion, reason);
  logSerial(temp, hum, dist, light, motion, reason);

  delay(2000);   // DHT22 needs about 2 s between reads
}
