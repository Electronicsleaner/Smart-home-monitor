# Day 6: Test results (Wokwi simulation)

Normal state for every test: 24 C, 40 %, HC-SR04 at 100 cm, LDR at its default position.

| # | Test | Input | Expected | Actual | Pass/Fail |
|---|---|---|---|---|---|
| 1 | Normal state | defaults | `Alarm=NONE`, LCD "Status: Normal", green LED on, buzzer off | ___ | ___ |
| 2 | Temperature reading | 30 C | `T=30.0`, `Alarm=NONE` | ___ | ___ |
| 3 | Humidity reading | 70 % | `H=70`, `Alarm=NONE` | ___ | ___ |
| 4 | High temp alarm | 36 C | `Alarm=HIGH TEMP`, red LED, buzzer, LCD "ALARM:HIGH TEMP" | ___ | ___ |
| 5a | Boundary below | 35.0 C | `Alarm=NONE` (alarm needs temp above 35.0) | ___ | ___ |
| 5b | Boundary above | 35.1 C | `Alarm=HIGH TEMP` | ___ | ___ |
| 6 | Close object | 5 cm | `Dist` near 5, `Alarm=TOO CLOSE`, red LED, buzzer | `Dist=4.9`, `Alarm=TOO CLOSE`, red LED and buzzer on | Pass |
| 7a | Distance accuracy | 50 cm | `Dist` between 49.5 and 51 | ___ | ___ |
| 7b | Distance accuracy | 200 cm | `Dist` between 199.5 and 201 | ___ | ___ |
| 8 | Dark alarm | LDR slider fully dark | `Light` above 600, `Alarm=TOO DARK`, red LED, buzzer | ___ | ___ |
| 9 | Motion | PIR triggered | `Motion=1`, LCD page 2 "Motion: YES", no alarm | ___ | ___ |
| 10 | Recovery | all back to normal | `Alarm=NONE`, green LED, buzzer off | ___ | ___ |
| 11 | Serial logging | any | one line about every 2 s | ___ | ___ |
| 12 | LCD paging | 10 s | page 1 (T, H) and page 2 (L, D, Motion) alternate | ___ | ___ |

## Calibration values
- DARK_THRESHOLD used: ___
- LDR reading in dark: ___  in bright: ___

## Screenshots
![Normal](screenshots/test01_normal.png)
![High temp](screenshots/test04_high_temp.png)
![Close object](screenshots/test06_close_object.png)
![Dark](screenshots/test08_dark.png)
![Serial log](screenshots/test11_serial_log.png)
