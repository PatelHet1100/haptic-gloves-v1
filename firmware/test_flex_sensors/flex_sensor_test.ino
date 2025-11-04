/*
  flex_sensor_test.ino
  Tests 5 flex sensors connected to ESP32.
  Prints analog values to Serial Monitor.
  Author: Het Patel
  Date: 2024-11
*/

#define NUM_FLEXS 5
const int flexPins[NUM_FLEXS] = {34, 35, 32, 33, 36}; // adjust per wiring

void setup() {
  Serial.begin(115200);
  Serial.println("Flex Sensor Test Started.");
}

void loop() {
  Serial.print("FLEX:");
  for (int i = 0; i < NUM_FLEXS; i++) {
    int value = analogRead(flexPins[i]);
    Serial.print(value);
    if (i < NUM_FLEXS - 1) Serial.print(",");
  }
  Serial.println();
  delay(100);
}
