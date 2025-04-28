# ESP32 Bluetooth Bridge

This project implements an ESP32-based bridge between a PC (via USB Serial) and an Arduino (ATmega328) master device, forwarding sensor data over Bluetooth.

## Features

- Acts as a middleman between:
  - **PC** ↔ **ESP32** (USB Serial)
  - **ESP32** ↔ **ATmega328 Master** (UART Serial2)
  - **ESP32** ↔ **Bluetooth Device** (Bluetooth Serial)
- Automatically sends a command (`3`) every 6 seconds to the ATmega328 master to request sensor data.
- Parses the received sensor data and re-formats it into a readable format.
- Forwards nicely formatted sensor readings over Bluetooth.
- Allows manual commands from the PC to be forwarded to the master.

## How It Works

- Every 6 seconds, the ESP32 sends the command **"3"** to the ATmega328 master.
- The master responds with sensor data in the format:
  ```
  Sensor Data: D[D1:32,D2:455,D3:32,D4:940]
  ```
- The ESP32 parses and reformats the data:
  ```
  Temp [DS18]: 32
  Moisture Sensor: 455
  Temp [BME280]: 32
  Pressure [BME280]: 940
  ```
- The formatted data is then sent over Bluetooth using the device name **"ESP32_BT_Bridge"**.
- Manual input from the PC Serial Monitor can also be forwarded to the master.

## Requirements

- **ESP32** Development Board
- **ATmega328**-based master device (Arduino Uno/Nano)
- PC connected via USB to ESP32
- Bluetooth-capable device (phone, tablet, or computer)

## Pin Mapping

| ESP32 Pin | Function                             |
|-----------|--------------------------------------|
| GPIO16    | UART2 RX (receive from Arduino)       |
| GPIO17    | UART2 TX (send to Arduino)            |

## Project Structure

```
/YourRepository
 ├── ESP32/
 │    └── ESP32_Bridge.ino  # ESP32 code to bridge UART and Bluetooth
 └── README.md              # Project documentation
```

## License

This project is open-source and available under the [MIT License](LICENSE).


