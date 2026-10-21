# Smart Home Environment Monitoring System

Embedded Systems & IoT Internship, Task 1.

An Arduino Uno system that reads temperature, humidity, light, distance and motion, shows the values on an I2C LCD, logs them over the Serial Monitor every 2 seconds, and raises alarms with LEDs and a buzzer. Built and tested in the Wokwi simulator.

**Wokwi project:** [paste your Wokwi link here]

## Features
- Temperature and humidity monitoring (DHT22)
- Light intensity detection (LDR module)
- Distance measurement (HC-SR04)
- Motion detection (PIR)
- 16x2 I2C LCD with two alternating pages
- Green and red status LEDs and a buzzer alarm
- Serial data logging, one line per cycle
- Modular code: one function per sensor and one alarm decision function

## Components
| Component | Quantity | Purpose |
|---|---|---|
| Arduino Uno | 1 | Microcontroller |
| DHT22 | 1 | Temperature and humidity |
| HC-SR04 | 1 | Distance |
| LDR module | 1 | Light level |
| PIR sensor | 1 | Motion |
| 16x2 I2C LCD | 1 | Display |
| Buzzer | 1 | Alarm sound |
| LEDs (green, red) | 2 | Status indicators |
| 220 ohm resistors | 2 | LED current limiting |

## Pin connections
| Component | Pin | Arduino |
|---|---|---|
| DHT22 | SDA (data) | D2 |
| HC-SR04 | TRIG | D3 |
| HC-SR04 | ECHO | D4 |
| PIR | OUT | D5 |
| LDR module | AO | A0 |
| Buzzer | + | D8 |
| Green LED | anode (via 220 ohm) | D9 |
| Red LED | anode (via 220 ohm) | D10 |
| I2C LCD | SDA / SCL | A4 / A5 |

Every VCC goes to 5V and every GND to GND. LED cathodes and the buzzer's second pin go to GND.

## Circuit diagrams
**Block diagram**

![Block diagram](diagrams/block_diagram.png)

**Wiring diagram** (signal pins; power connections are listed in the pin table above)

![Wiring diagram](diagrams/wiring_diagram.png)

**Simulation circuit (Wokwi)**

![Simulation circuit](diagrams/circuit_simulation.png)

## Alarm conditions
| Condition | Threshold | Result |
|---|---|---|
| High temperature | above 35 C | Red LED, buzzer, LCD "ALARM:HIGH TEMP" |
| Object too close | below 10 cm | Red LED, buzzer, LCD "ALARM:TOO CLOSE" |
| Too dark | LDR reading above 600 | Red LED, buzzer, LCD "ALARM:TOO DARK" |

The Wokwi LDR module reads about 16 in bright light and about 866 in the dark, so the dark threshold of 600 sits between the two. Real hardware will need re-calibration.

## Setup instructions
1. Open [Wokwi](https://wokwi.com) and create a new **Arduino Uno** project.
2. In the Library Manager, add **DHT sensor library** (Adafruit) and **LiquidCrystal I2C**.
3. Open the `diagram.json` tab and paste `simulation/smart_home_diagram.json`.
4. Open `sketch.ino` and paste `src/smart_home_monitor.ino`.
5. Press Play, then use the sensor sliders to test each alarm.

## Sample output
```
T=24.0,H=70,Light=351,Dist=4.9,Motion=0,Alarm=TOO CLOSE
[paste one normal line from your Serial Monitor here]
[paste one HIGH TEMP line from your Serial Monitor here]
```

## Testing
12 tests were run in the Wokwi simulator and recorded with the Serial line, LCD text and LED/buzzer state for each. See [`tests/test_results.md`](tests/test_results.md) for the full table and [`docs/day6_notes.md`](docs/day6_notes.md) for validation notes.

![Normal state](docs/screenshots/test01_normal.png)
![High temperature alarm](docs/screenshots/test04_high_temp.png)
![Close object alarm](docs/screenshots/test06_close_object.png)
![Dark alarm](docs/screenshots/test08_dark.png)
![Serial log](docs/screenshots/test11_serial_log.png)

## Repository structure
```
src/          Arduino sketches for each day and the final project
simulation/   Wokwi diagram.json files
diagrams/     Block diagram, wiring diagram, simulation circuit
docs/         Daily notes, architecture and screenshots
tests/        Test results
```

## Daily progress
| Day | Topic | Notes |
|---|---|---|
| 1 | LED and push button | [day1_notes.md](docs/day1_notes.md) |
| 2 | Potentiometer, PWM, LDR | [day2_notes.md](docs/day2_notes.md) |
| 3 | DHT22 and HC-SR04 | [day3_notes.md](docs/day3_notes.md) |
| 4 | I2C LCD, buzzer, LEDs | [day4_notes.md](docs/day4_notes.md) |
| 5 | Full integration | [day5_notes.md](docs/day5_notes.md) |
| 6 | Testing and diagrams | [day6_notes.md](docs/day6_notes.md) |

## Issues and fixes
| Problem | Cause | Fix |
|---|---|---|
| Button always read 0 | Both wires on internally connected legs | Moved the GND wire to the opposite row |
| Library not found | Typo "DTH" in the search | Searched "DHT sensor library" |
| Dark alarm at default light | Threshold set before calibration | Measured dark and bright readings and set the threshold between them |

## Hardware notes
Built and tested in simulation only. For a real build, use the same pin plan, a 220 ohm resistor per LED, check the LCD I2C address (0x27 or 0x3F), and re-calibrate the dark threshold because real LDR values differ.

## Future work (Task 2)
ESP32, Wi-Fi, MQTT and a cloud dashboard.

## Author
[Your name], Embedded Systems & IoT Internship
