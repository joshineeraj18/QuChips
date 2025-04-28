Arduino I2C Master Controller
This project implements an Arduino-based I2C master device that communicates with a slave device (ATmega328) to retrieve various types of data.

Features
Provides an interactive menu via Serial Monitor.

Sends specific commands to the I2C slave:

Get Device ID (Command 1)

Get Available Data Size (Command 2)

Get Sensor Data (Command 3)

Get Device Name (Command 4)

Displays the received information on the Serial Monitor.

Simple and lightweight design for easy expansion.

How It Works
The master uses the Wire.h library to communicate over I2C (Slave Address: 0x08).

User interacts via the Serial Monitor at 9600 baud rate.

Each menu option sends a command byte to the slave.

Slave responds with requested information, which is printed on the Serial Monitor.

Requirements
Arduino board (e.g., Uno, Nano with ATmega328P).

I2C pull-up resistors (typically 4.7kΩ) on SDA and SCL lines.

Properly programmed slave device responding to the command protocol.

Usage
Connect your Arduino to the PC and upload the master sketch.

Open the Serial Monitor at 9600 baud.

Select an option (1–4) by typing a number and pressing Enter.

View the responses from the slave device on the Serial Monitor.
