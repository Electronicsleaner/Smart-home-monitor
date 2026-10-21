# Day 3: DHT22 and HC-SR04

**Code:** `src/day3_dht22_hcsr04.ino`  **Circuit:** `simulation/day3_diagram.json`
![Day 3 circuit](screenshots/day3_circuit.png)

## Wiring
| Sensor pin | Uno pin |
|---|---|
| DHT22 VCC | 5V |
| DHT22 SDA | D2 |
| DHT22 GND | GND |
| HC-SR04 VCC | 5V |
| HC-SR04 TRIG | D3 |
| HC-SR04 ECHO | D4 |
| HC-SR04 GND | GND |

## Test results
| DHT22 slider | Expected | Serial reading |
|---|---|---|
| 24.8 C, 40.5 % | 24.80 C, 40.50 % | 24.80 C, 40.50 % |
| 40 C, 80 % | 40.00 C, 80.00 % | ___ |

| HC-SR04 slider | Expected (within 1 cm) | Serial reading |
|---|---|---|
| 10 cm | about 10 cm | ___ |
| 100 cm | about 100 cm | ___ |
| 300 cm | about 300 cm | ___ |
| 400 cm (default) | about 400 cm | 401.14 cm |

## Notes
- The DHT22 uses a single-wire digital protocol for temperature and humidity.
- Distance = echo time x 0.0343 cm/us / 2 (sound travels out and back).
- `pulseIn` has a 30 ms timeout so the program never hangs.
- Each sensor was tested alone before integration.

## Issue log
- Problem: library search returned unrelated results.
- Cause: typo ("DTH") in the Library Manager search.
- Fix: searched "DHT sensor library" (Adafruit).
