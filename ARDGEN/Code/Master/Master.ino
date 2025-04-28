/*
  Arduino I2C Master Controller
  ------------------------------

  This sketch acts as a master controller communicating with an ATmega328-based slave device over the I2C bus.

  Functionality:
  - Presents a simple menu over Serial Monitor (USB) to the user.
  - Allows the user to send different commands to the slave:
      1. Get Device ID
      2. Get Available Data Size
      3. Request Sensor Data
      4. Get Device Name
  - Reads and displays the response from the slave on the Serial Monitor.

  Communication Details:
  - Master uses I2C (Wire library) with slave address 0x08.
  - Slave device responds to different command codes with the requested information.
  - The master also handles basic error checking if data is not available.

  Usage:
  - Open the Serial Monitor at 9600 baud.
  - Select options by entering numbers 1–4 to interact with the slave device.
  - Sensor data is formatted and printed to the Serial Monitor.

  Author: Neeraj Joshi
  Date: 29/April/2025

  Note: Ensure that pull-up resistors (typically 4.7kΩ) are present on SDA and SCL lines for reliable I2C communication.
*/

#include <Wire.h>

#define SLAVE_ADDRESS 8

void setup() {
  Wire.begin(); // Join I2C bus as master
  Serial.begin(9600); // For printing menu and output
  delay(500); // Give time for setup
}

void loop() {
  showMenu();
  while (!Serial.available()) {
    // Wait for user input
  }

  char userInput = Serial.read();

  switch (userInput) {
    case '1':
      requestID();
      break;
    case '2':
      requestDataSize();
      break;
    case '3':
      requestSensorData();
      break;
    case '4':
      requestDeviceName();
      break;
    default:
      Serial.println("Invalid option. Try again.");
      break;
  }

  delay(1000); // Give some time before showing menu again
}

void showMenu() {
  Serial.println("\n=== I2C Master Menu ===");
  Serial.println("1. Get Device ID");
  Serial.println("2. Get Available Data Size");
  Serial.println("3. Get Sensor Data");
  Serial.println("4. Get Device Name");
  Serial.print("Enter choice: ");
}

void requestID() {
  Wire.beginTransmission(SLAVE_ADDRESS);
  Wire.write(1); // Command 1: Get ID
  Wire.endTransmission();

  Wire.requestFrom(SLAVE_ADDRESS, 2); // ID is 2 bytes
  if (Wire.available() >= 2) {
    byte high = Wire.read();
    byte low = Wire.read();
    uint16_t id = (high << 8) | low;
    Serial.print("Device ID: 0x");
    Serial.println(id, HEX);
  } else {
    Serial.println("Failed to read ID");
  }
}

void requestDataSize() {
  Wire.beginTransmission(SLAVE_ADDRESS);
  Wire.write(2); // Command 2: Get Data Size
  Wire.endTransmission();

  Wire.requestFrom(SLAVE_ADDRESS, 2); // Size is 2 bytes
  if (Wire.available() >= 2) {
    byte high = Wire.read();
    byte low = Wire.read();
    uint16_t size = (high << 8) | low;
    Serial.print("Available Data Size: ");
    Serial.println(size);
  } else {
    Serial.println("Failed to read Data Size");
  }
}

void requestSensorData() {  
  // First get the data size
  Wire.beginTransmission(SLAVE_ADDRESS);
  Wire.write(2); // Command 2 to get size
  Wire.endTransmission();

  Wire.requestFrom(SLAVE_ADDRESS, 2);
  uint16_t size = 0;
  if (Wire.available() >= 2) {
    byte high = Wire.read();
    byte low = Wire.read();
    size = (high << 8) | low;
  } else {
    Serial.println("Failed to get size before requesting data");
    return;
  }

  // Now request actual data
  Wire.beginTransmission(SLAVE_ADDRESS);
  Wire.write(3); // Command 3: Get Data
  Wire.endTransmission();

  Wire.requestFrom(SLAVE_ADDRESS, size);
  
  Serial.print("Sensor Data: ");
  while (Wire.available()) {
    char c = Wire.read();
    Serial.print(c);
  }
  Serial.println();
}

void requestDeviceName() {
  Wire.beginTransmission(SLAVE_ADDRESS);
  Wire.write(4); // Command 4: Get Name
  Wire.endTransmission();

  Wire.requestFrom(SLAVE_ADDRESS, 9); // Name "DeviceXYZ" = 9 chars

  Serial.print("Device Name: ");
  while (Wire.available()) {
    char c = Wire.read();
    Serial.print(c);
  }
  Serial.println();
}
