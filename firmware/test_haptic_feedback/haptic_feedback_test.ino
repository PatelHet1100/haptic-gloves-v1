
/*
  haptic_feedback_test.ino
  Triggers all five vibration motors when ESP32 receives
  a BLE mouse click signal or button press from code.
  Author: Het Patel
  Date: 2024-11
*/

#include <BleMouse.h>

BleMouse bleMouse("HapticGlove_Feedback", "HetPatel", 100);

const int motorPins[5] = {12, 13, 14, 27, 26}; // adjust per wiring
const int pulseTime = 150; // ms

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < 5; i++) {
    pinMode(motorPins[i], OUTPUT);
    digitalWrite(motorPins[i], LOW);
  }
  bleMouse.begin();
  Serial.println("Haptic Feedback Test Ready.");
}

void loop() {
  if (!bleMouse.isConnected()) {
    delay(200);
    return;
  }

  // Simulate trigger when you click left button on mouse or after 5 sec
  static unsigned long lastTrigger = 0;
  if (millis() - lastTrigger > 5000) {
    triggerFeedback();
    lastTrigger = millis();
  }

  delay(50);
}

void triggerFeedback() {
  Serial.println("Feedback pulse!");
  for (int i = 0; i < 5; i++) digitalWrite(motorPins[i], HIGH);
  delay(pulseTime);
  for (int i = 0; i < 5; i++) digitalWrite(motorPins[i], LOW);
}
