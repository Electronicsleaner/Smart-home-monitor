# Day 1: LED and push button

**Code:** `src/day1_blink_button.ino`  **Circuit:** `simulation/day1_diagram.json`
![Day 1 circuit](screenshots/day1_circuit.png)

## Description
This circuit uses an Arduino Uno to control a red LED with a push button. The LED connects to pin 13 through a 220 ohm resistor, and the button connects between pin 2 and GND using the internal pull-up resistor. When the button is released, pin 2 reads HIGH (1) and the LED stays off, and when it is pressed, the pin reads LOW (0) and the LED turns on. The Serial Monitor prints the button state every 100 ms for verification and debugging.

## Wiring
| From | To |
|---|---|
| Uno pin 13 | Resistor (220 ohm) |
| Resistor | LED anode |
| LED cathode | GND |
| Button, top-left leg | Uno pin 2 |
| Button, bottom-right leg | GND |

## LED resistor calculation
R = (5 V - 2 V) / 0.015 A = 200 ohm, so the nearest standard value, 220 ohm, is used.
Actual current = (5 - 2) / 220 = about 13.6 mA, which is safe for the LED.

## Test results
| Button | Pin 2 | Serial | LED |
|---|---|---|---|
| Released | HIGH | 1 | Off |
| Pressed | LOW | 0 | On |

## Issue log
- Problem: Serial printed 0 constantly and the LED stayed on.
- Cause: both button wires were on legs that are connected inside the button, so pin 2 was shorted to GND.
- Fix: moved the GND wire to the opposite row, so the switch sits between pin 2 and GND.
