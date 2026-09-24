# Wi-Fi Control Test

## Objective

To test Wi-Fi communication between the ESP32 and a web browser.

## Test

1. Upload the program to ESP32.
2. Connect phone/computer to RobotArm Wi-Fi.
3. Open the ESP32 IP address in a browser.
4. Press Send Test Command.
5. Check the Serial Monitor.

## Expected Result

The ESP32 should receive:

```
TEST,1
```

The browser should display:

```
Test command received
```

## Result

**PASS** – Wi-Fi connection, web page, and WebSocket communication can be tested successfully.

## Note

This test checks communication only. It does not test servo movement.
