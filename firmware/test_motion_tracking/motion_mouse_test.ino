/*
  motion_mouse_test.ino
  ESP32 + MPU6050 → acts as a BLE mouse.
  Move your hand → cursor moves on PC or phone.
  Author: Het Patel
  Date: 2024-11
*/

#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <BleMouse.h>

Adafruit_MPU6050 mpu;
BleMouse bleMouse("HapticGlove_Mouse", "HetPatel", 100);

float prevX = 0, prevY = 0;
const float alpha = 0.8; // smoothing factor

void setup() {
  Serial.begin(115200);
  Wire.begin();
  if (!mpu.begin()) {
    Serial.println("MPU6050 not found. Check wiring!");
    while (1) delay(10);
  }
  Serial.println("MPU6050 ready.");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  bleMouse.begin();
  Serial.println("BLE Mouse initialized.");
}

void loop() {
  if (!bleMouse.isConnected()) {
    delay(200);
    return;
  }

  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Use gyro for smoother motion
  float gx = g.gyro.x; // rad/s
  float gy = g.gyro.y;

  // basic smoothing
  prevX = alpha * prevX + (1 - alpha) * gx * 200;
  prevY = alpha * prevY + (1 - alpha) * gy * 200;

  // Move cursor
  int dx = constrain((int)prevX, -15, 15);
  int dy = constrain((int)prevY, -15, 15);
  bleMouse.move(dx, dy);

  delay(20); // 50 Hz update
}
