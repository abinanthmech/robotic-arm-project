#include <Arduino.h>
#include <ESP32Servo.h>

Servo servo;

const int SERVO_PIN = 27;

struct Step {
  int angle;
  unsigned long delayTime;
};

Step steps[10];
int stepCount = 0;

void setup() {

  Serial.begin(115200);

  servo.attach(SERVO_PIN, 500, 2500);

  Serial.println("Record & Playback Test");

  // Record sample movements
  steps[0] = {60, 1000};
  steps[1] = {120, 1000};
  steps[2] = {90, 1000};

  stepCount = 3;

  Serial.println("Movements recorded.");
}

void loop() {

  Serial.println("Playing recorded movements...");

  for (int i = 0; i < stepCount; i++) {

    servo.write(steps[i].angle);

    delay(steps[i].delayTime);
  }

  Serial.println("Playback complete.");

  delay(2000);
}

