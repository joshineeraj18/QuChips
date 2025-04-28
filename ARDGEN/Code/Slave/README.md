Arduino I2C Slave Device
This project implements an Arduino-based I2C slave device that collects sensor data and responds to commands from an I2C master.

Features
Acts as an I2C slave (Address 0x08) and responds to specific requests from the master.

Gathers data from multiple sensors:

DS18B20 Temperature Sensor (OneWire)

Analog Moisture Sensor (connected to A1)

BME280 Sensor for Temperature and Pressure

Prepares and formats the sensor data into a structured string.

Supports 4 command types:

Get Device ID

Get Available Data Size

Get Sensor Data

Get Device Name

How It Works
Upon receiving a command via I2C, the slave:

Sends a unique ID (0x1234) if requested.

Sends the size of the current sensor data string.

Sends the actual sensor data string in the format:

ruby
Copy
Edit
D[D1:TempDS18B20,D2:Moisture,D3:TempBME,D4:PressureBME]
Sends a device name ("DeviceXYZ") for identification.

Sensor readings are refreshed every 500 milliseconds.

Requirements
Arduino board (e.g., Uno, Nano with ATmega328P).

Sensors:

DS18B20 Temperature Sensor (connected to A0)

Moisture Sensor (analog, connected to A1)

BME280 Temperature/Pressure Sensor (I2C Address 0x76)

I2C pull-up resistors (typically 4.7kΩ) on SDA and SCL lines.

Usage
Connect the slave device to sensors and ensure correct wiring.

Upload the provided code to the Arduino.

The slave will start gathering sensor data continuously.

It will respond to commands from the master device accordingly.

Project Structure
bash
Copy
Edit
/YourRepository
 ├── Slave/
 │    └── Slave.ino      # Arduino slave code to respond over I2C
 └── README.md           # Project documentation
License
This project is open-source and available under the MIT License.
