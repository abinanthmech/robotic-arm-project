# Record and Playback Test

## Objective
To test recording and playback of servo movements.

## Test
1. Upload the test code to ESP32.
2. The program stores three servo positions.
3. The servo plays the stored positions in sequence.
4. Observe the servo movement.

## Expected Result
The servo should move:

```text
60° → 120° → 90°
```

## Result
**PASS** – The programmed movement sequence is played back successfully.

## Note
This is a simplified functional test of the record/playback concept. The complete robotic arm uses the same concept with multiple servos and recorded steps.
