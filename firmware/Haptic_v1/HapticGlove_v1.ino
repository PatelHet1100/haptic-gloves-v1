/*
  HapticGlove_v1.ino
  Author: Het Patel
  Date: 2024-11

  Integrates:
    - MPU6050 motion tracking → cursor movement
    - Flex sensors → gesture detection (clicks, scroll)
    - Haptic motors → vibration feedback
    - BLE Mouse HID → direct pairing with PC or phone

  Behavior:
    - Move hand → moves cursor
    - Bend index → Left click
    - Bend middle → Right click
    - Both bent → haptic pulse feedback
*/

#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <BleMouse.h>

// === Hardware Configuration ===
Adafruit_MPU6050 mpu;
BleMouse bleMouse("HapticGlove_v1", "HetPatel", 100);

const int flexPins[5] = {34, 35, 32, 33, 36}; // adjust per wiring
const int motorPins[5] = {12, 13, 14, 27, 26}; // through MOSFET/transistor

// === Gesture Thresholds ===
int flexBaseline[5];        // baseline (flat hand)
int flexThreshold = 300;    // bend difference for gesture detection
bool clickStateLeft = false;
bool clickStateRight = false;

// === Motion Variables ===
float prevX = 0, prevY = 0;
const float alpha = 0.8; // smoothing
const float scale = 200; // motion sensitivity

// === Haptic ===
const int hapticPulse = 150; // ms

void setup() {
  Serial.begin(115200);
  Wire.begin();

  // --- Setup MPU6050 ---
  if (!mpu.begin()) {
    Serial.println("MPU6050 not found. Check wiring!");
    while (1) delay(10);
  }
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.println("MPU6050 ready.");

  // --- Setup BLE Mouse ---
  bleMouse.begin();
  Serial.println("BLE Mouse initialized.");

  // --- Setup Flex Sensors ---
  for (int i = 0; i < 5; i++) {
    pinMode(flexPins[i], INPUT);
    flexBaseline[i] = analogRead(flexPins[i]);
  }
  Serial.println("Flex sensors calibrated.");

  // --- Setup Motors ---
  for (int i = 0; i < 5; i++) {
    pinMode(motorPins[i], OUTPUT);
    digitalWrite(motorPins[i], LOW);
  }
  Serial.println("Motors ready.");

  Serial.println("System startup complete. Pair via Bluetooth: 'HapticGlove_v1'");
}

void loop() {
  if (!bleMouse.isConnected()) {
    delay(200);
    return;
  }

  // === MOTION CONTROL ===
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  float gx = g.gyro.x;
  float gy = g.gyro.y;

  prevX = alpha * prevX + (1 - alpha) * gx * scale;
  prevY = alpha * prevY + (1 - alpha) * gy * scale;

  int dx = constrain((int)prevX, -15, 15);
  int dy = constrain((int)prevY, -15, 15);
  bleMouse.move(dx, dy);

  // === FLEX SENSOR INPUT ===
  int flexValues[5];
  for (int i = 0; i < 5; i++) flexValues[i] = analogRead(flexPins[i]);

  bool indexBent = flexValues[0] - flexBaseline[0] > flexThreshold;
  bool middleBent = flexValues[1] - flexBaseline[1] > flexThreshold;

  // === GESTURE: Left Click (Index) ===
  if (indexBent && !clickStateLeft) {
    bleMouse.click(MOUSE_LEFT);
    triggerHaptic(0);
    clickStateLeft = true;
  } else if (!indexBent) clickStateLeft = false;

  // === GESTURE: Right Click (Middle) ===
  if (middleBent && !clickStateRight) {
    bleMouse.click(MOUSE_RIGHT);
    triggerHaptic(1);
    clickStateRight = true;
  } else if (!middleBent) clickStateRight = false;

  // === DOUBLE GESTURE: Both Bent → Pulse All Motors ===
  if (indexBent && middleBent) {
    triggerAllHaptic();
  }

  delay(20);
}

// === FUNCTIONS ===
void triggerHaptic(int motorIndex) {
  digitalWrite(motorPins[motorIndex], HIGH);
  delay(hapticPulse);
  digitalWrite(motorPins[motorIndex], LOW);
}

void triggerAllHaptic() {
  for (int i = 0; i < 5; i++) digitalWrite(motorPins[i], HIGH);
  delay(hapticPulse);
  for (int i = 0; i < 5; i++) digitalWrite(motorPins[i], LOW);
}
