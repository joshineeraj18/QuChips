#include <Wire.h>

#define BATTERY_SENSOR_PIN A3
#define I2C_SLAVE_ADDRESS 0x12

volatile uint16_t batteryVoltageRaw = 0;

void setup() {
  analogReference(DEFAULT);  // Uses 5V or 3.3V as reference
  pinMode(BATTERY_SENSOR_PIN, INPUT);

  Wire.begin(I2C_SLAVE_ADDRESS);     // Start I2C as slave
  Wire.onRequest(sendBatteryData);   // Register request handler

  // Optionally start serial for debugging
  Serial.begin(9600);
}

void loop() {
  batteryVoltageRaw = analogRead(BATTERY_SENSOR_PIN);
  delay(1000); // Read every 1 second
}

// I2C handler function
void sendBatteryData() {
  // Send 2 bytes (MSB + LSB)
  Wire.write(highByte(batteryVoltageRaw));
  Wire.write(lowByte(batteryVoltageRaw));
}
