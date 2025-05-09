#include <Wire.h>

#define HAL_SENSOR_PIN A2
#define I2C_SLAVE_ADDRESS 0x13

volatile uint16_t halSensorValue = 0;

void setup() {
  analogReference(DEFAULT);  // Reference voltage: 5V or 3.3V depending on board
  pinMode(HAL_SENSOR_PIN, INPUT);

  Wire.begin(I2C_SLAVE_ADDRESS);     // Initialize I2C as slave
  Wire.onRequest(sendHalSensorData); // Register function for request

}

void loop() {
  halSensorValue = analogRead(HAL_SENSOR_PIN); // Read HAL sensor
  delay(100); // Optional debounce or sample rate delay
}

// I2C handler function to send sensor data
void sendHalSensorData() {
  Wire.write(highByte(halSensorValue));
  Wire.write(lowByte(halSensorValue));
}
