#include <Arduino.h>
#include <ESP32Servo.h>

Servo testServo;

const int SERVO_PIN = 27;   // Base servo

void setup() {
  Serial.begin(115200);

  testServo.attach(SERVO_PIN, 500, 2500);

  Serial.println("Servo Test Started");

  testServo.write(90);
  delay(1000);
}

void loop() {

  // Move 0° → 180°
  for (int angle = 0; angle <= 180; angle++) {
    testServo.write(angle);
    delay(15);
  }

  delay(500);

  // Move 180° → 0°
  for (int angle = 180; angle >= 0; angle--) {
    testServo.write(angle);
    delay(15);
  }

  delay(500);
}
