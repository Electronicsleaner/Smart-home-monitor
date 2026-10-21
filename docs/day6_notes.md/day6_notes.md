# Day 6: Validation and debugging notes

## Final circuit (Wokwi)
![Final circuit](screenshots/day6_circuit.png)

The final circuit has the DHT22, HC-SR04, PIR and LDR module on the bottom row, the I2C LCD at the top left, and the buzzer, green LED and red LED (each LED with a 220 ohm resistor) at the top right. All connections follow the pin table in `day5_notes.md`.

## Validation method
This project was built and tested in the Wokwi simulator (no physical hardware). Serial Monitor output and LCD, LED and buzzer behaviour were used to validate each sensor and alarm. Multimeter checks apply to a hardware build and are listed as planned steps if the circuit is built physically:
- Check the 5V rail in DC voltage mode
- Check the voltage across each LED (about 2 V expected)
- Continuity test on each wire before powering on

## Debugging log
| Problem | Symptom | Cause | Fix |
|---|---|---|---|
| Button always read 0 (Day 1) | Serial printed 0, LED always on | Both wires on connected legs | Moved GND wire to the opposite row |
| Library not found (Day 3) | Search showed unrelated results | Typo "DTH" | Searched "DHT sensor library" |
| Dark alarm at default light (Day 6) | TOO DARK shown in normal light | Threshold set before calibration | Measured dark and bright readings and set the threshold between them |
| Buzzer stayed on after DHT22 error | LEDs and buzzer kept last state | Early return skipped output update | Turn off buzzer and LEDs in the error branch |
