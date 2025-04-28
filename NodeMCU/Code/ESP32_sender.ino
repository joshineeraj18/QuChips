#include "BluetoothSerial.h"

BluetoothSerial SerialBT;  // Bluetooth Serial object

#define RXD2 16
#define TXD2 17

unsigned long lastRequestTime = 0;
const unsigned long requestInterval = 6000; // 3 seconds

void setup() {
  Serial.begin(9600);  // USB Serial for PC connection
  SerialBT.begin("ESP32_BT_Bridge");  // Bluetooth device name
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);  // UART2 for ATmega328 master

  Serial.println("ESP32 ready. Waiting for data...");
}

void loop() {
  unsigned long currentMillis = millis();

  // Every 3 seconds, send command "3" to ATmega328
  if (currentMillis - lastRequestTime >= requestInterval) {
    Serial2.print("3");  // Send command 3 (followed by newline)
    lastRequestTime = currentMillis;
  }

  // If data comes from ATmega328 master (Serial2)
  if (Serial2.available()) 
  {
    String incomingFromArduino = Serial2.readStringUntil('\n');
    incomingFromArduino.trim();  // Remove unwanted \r\n if needed
    if (incomingFromArduino.startsWith("Sensor Data: D[")) {
      // Process the incoming sensor data
      parseAndSendData(incomingFromArduino);
    } else {
      // Unexpected data, just forward to Serial Monitor
      Serial.println("[From Arduino]: " + incomingFromArduino);
    }
  }

  // If data comes manually from PC (Serial Monitor)
  if (Serial.available()) 
  {
    String incomingFromPC = Serial.readStringUntil('\n');
    incomingFromPC.trim();
    if (incomingFromPC.length() > 0) {
      Serial2.print(incomingFromPC); // Forward to Arduino
      Serial.println("[sent]:" + incomingFromPC);
    }
  }
}

// Function to parse and forward sensor data nicely
void parseAndSendData(String rawData) {
  Serial.println("Raw Data: " + rawData);

  // Example rawData: Sensor Data: D[D1:32,D2:455,D3:32,D4:940]
  int startIdx = rawData.indexOf('[');
  int endIdx = rawData.indexOf(']');
  
  if (startIdx == -1 || endIdx == -1 || endIdx <= startIdx) {
    Serial.println("Invalid data format!");
    return;
  }

  String sensorPart = rawData.substring(startIdx + 1, endIdx); // Extract D1:32,D2:455,...
    SerialBT.println();    
    SerialBT.println();    
    SerialBT.println();    
    SerialBT.println("======Data======");
  // Split each "Dx:Value"
  while (sensorPart.length() > 0) {
    int commaIdx = sensorPart.indexOf(',');
    String pair;
    if (commaIdx != -1) {
      pair = sensorPart.substring(0, commaIdx);
      sensorPart = sensorPart.substring(commaIdx + 1);
    } else {
      pair = sensorPart;
      sensorPart = "";
    }


    
    int colonIdx = pair.indexOf(':');
    if (colonIdx != -1) {
      String key = pair.substring(0, colonIdx);
      String value = pair.substring(colonIdx + 1);

      // Map the key to description
      String description = "";
      if (key == "D1") description = "Temp [DS18]";
      else if (key == "D2") description = "Moisture Sensor";
      else if (key == "D3") description = "Temp [BME280]";
      else if (key == "D4") description = "Pressure [BME280]";
      else description = key;

      // Send nicely formatted string to Bluetooth
      String formatted = description + ": " + value;
      Serial.println("-> " + formatted);
      SerialBT.println(formatted);
    }
  }
}
