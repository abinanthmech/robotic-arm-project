# Wiring

## Servo Connections

The six servo motors are connected to the ESP32 as follows:

| Servo | ESP32 GPIO |
|---|---:|
| Base | 27 |
| Shoulder | 26 |
| Elbow | 25 |
| Wrist Pitch | 14 |
| Wrist Roll | 12 |
| Gripper | 33 |

## Notes

The ESP32 controls the position of each servo through its assigned GPIO pin.
