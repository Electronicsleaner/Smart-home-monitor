# Day 5: Full system integration

**Code:** `src/smart_home_monitor.ino`  **Circuit:** `simulation/smart_home_diagram.json`

## Pin plan
| Component | Uno pin |
|---|---|
| DHT22 SDA | D2 |
| HC-SR04 TRIG / ECHO | D3 / D4 |
| PIR OUT | D5 |
| Buzzer + | D8 |
| Green LED via 220 ohm | D9 |
| Red LED via 220 ohm | D10 |
| LDR module AO | A0 |
| LCD SDA / SCL | A4 / A5 |

## Thresholds
| Condition | Value |
|---|---|
| High temperature | above 35 C |
| Object too close | below 10 cm |
| Too dark | LDR reading above 600 (DARK_IF_LOW = false) |

## Calibration
The Wokwi LDR module gives a HIGH reading in the dark and a LOW reading in bright light, so the sketch uses `DARK_IF_LOW = false`.

| Reading | Value | Source |
|---|---|---|
| Bright light | 16 | Day 2 LDR test |
| Dark | 866 | Day 2 LDR test |
| Default slider position | 250 | Day 5/6 Serial log |
| Default slider position (Test 6 run) | 351 | Day 6 Serial log |
| Day 5 dark reading | ___ | Fill in from your Day 5 or Test 8 run |

`DARK_THRESHOLD = 600` sits between the bright and dark readings, so the default positions (250 and 351) give no alarm and a dark setting (above 600) does.

## Design notes
- One function per sensor, one `checkAlarm()` function, separate output functions for LEDs/buzzer, LCD and Serial.
- The 16x2 LCD alternates between two pages every 2 seconds.
- `pulseIn` uses a timeout so a missing echo cannot hang the program.
- The Serial log prints one line per cycle: `T=24.0,H=40,Light=250,Dist=100.0,Motion=0,Alarm=NONE`.

## Industry challenge mapping
Reads multiple sensors, displays values, detects abnormal conditions, triggers alarms, and logs through the serial interface.
