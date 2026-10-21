# Day 2: Potentiometer, PWM and LDR

**Code:** `src/day2_pot_ldr.ino`  **Circuit:** `simulation/day2_diagram.json`
![Day 2 circuit](screenshots/day2_circuit.png)

## Wiring
| Component | Arduino |
|---|---|
| Potentiometer SIG | A0 |
| Potentiometer VCC / GND | 5V / GND |
| LDR module AO | A1 |
| LDR module VCC / GND | 5V / GND |
| LED via 220 ohm | D9 (PWM) |

## Concepts
- **ADC:** the Uno has a 10-bit ADC, so 0 to 5 V becomes 0 to 1023 (about 4.88 mV per step).
- **PWM:** `analogWrite(pin, 0-255)` changes the duty cycle. Average voltage = 5 V x duty / 255. Only pins marked ~ support PWM, so the LED moved from pin 13 to pin 9.
- **map():** converts the 0-1023 range to the 0-255 range.

## Results
| Pot position | Pot value | Brightness | LED |
|---|---|---|---|
| Minimum | 0 | 0 | Off |
| Middle | 512 | 127 | Half bright |
| Maximum | 1023 | 255 | Full |

| LDR setting | Light reading |
|---|---|
| Dark | 866 |
| Bright | 16 |
