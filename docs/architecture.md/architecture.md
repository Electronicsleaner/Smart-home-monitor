# System architecture

```mermaid
flowchart LR
  DHT22 --> UNO[Arduino Uno]
  HCSR04[HC-SR04] --> UNO
  LDR --> UNO
  PIR --> UNO
  UNO --> LCD[I2C LCD]
  UNO --> LED[Status LEDs]
  UNO --> BUZ[Buzzer]
  UNO --> SER[Serial Monitor log]
```

## Data flow
1. Every 2 seconds the Arduino reads the DHT22, HC-SR04, LDR and PIR.
2. `checkAlarm()` compares the readings with the thresholds and returns one alarm reason, or none.
3. The same result drives the LEDs, buzzer, LCD and Serial log, so all outputs always agree.

See also: `diagrams/block_diagram.png` and `diagrams/wiring_diagram.png`.
