# Day 4: I2C LCD, buzzer and LED indicators

**Code:** `src/day4_lcd_alarm.ino`  **Circuit:** `simulation/day4_diagram.json`

## Wiring
| Component | Uno pin |
|---|---|
| LCD SDA / SCL | A4 / A5 |
| LCD VCC / GND | 5V / GND |
| Buzzer + | D8 |
| Green LED via 220 ohm | D9 |
| Red LED via 220 ohm | D10 |
| DHT22 SDA | D2 |

## Results
| DHT22 temp | Expected | Observed |
|---|---|---|
| 24 C | LCD "T:24.0C H:__%" and "Status: Normal", green LED on, red LED off, buzzer off | ___ |
| 36 C | LCD "T:36.0C H:__%" and "ALARM: HIGH TEMP", green LED off, red LED on, buzzer on | ___ |
| 34.9 C (boundary) | No alarm: "Status: Normal", green LED on, red LED off, buzzer off | ___ |

The alarm threshold is 35.0 C, so 34.9 C must stay in the normal state.

## Notes
- **I2C** uses two wires, SDA (data) and SCL (clock). Each device has an address; the LCD uses 0x27. On the Uno, SDA is A4 and SCL is A5. A parallel LCD needs about 6 pins.
- `tone()` generates a square wave at the given frequency, and `noTone()` stops it.
- One `alarm` flag drives the LEDs, buzzer and LCD, so they always agree.
