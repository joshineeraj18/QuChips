#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define ONE_WIRE_BUS A0
#define I2C_SLAVE_ADDRESS 8

#define ID_HIGH 0x12
#define ID_LOW  0x34

#define NAME "DeviceXYZ" // 9 characters + null

#define SEALEVELPRESSURE_HPA (1013.25)

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
Adafruit_BME280 bme;

volatile byte receivedCommand = 0; // Store last received command
char sensorDataBuffer[40]; // Buffer for sensor data text

bool isBMEfound = false;
float tempBME = 0.0;
float presBME = 0.0;

void setup() {
  Wire.begin(I2C_SLAVE_ADDRESS); // Start I2C as slave
  Wire.onRequest(sendData);
  Wire.onReceive(receiveCommand);

  sensors.begin();

  if (bme.begin(0x76)) {
    isBMEfound = true;
  } else {
    isBMEfound = false;
  }

  pinMode(A1, INPUT);
}

void loop() {
  sensors.requestTemperatures();
  int a1Value = analogRead(A1);
  float tempC = sensors.getTempCByIndex(0);

  if (isBMEfound) {
    tempBME = bme.readTemperature();
    presBME = bme.readPressure() / 100.0F;
  }

  snprintf(sensorDataBuffer, sizeof(sensorDataBuffer),"D[D1:%d,D2:%d,D3:%d,D4:%d]",(int)tempC, a1Value, (int)tempBME, (int)presBME );

  delay(500); // Update every 0.5 seconds
}

void receiveCommand(int howMany) {
  if (howMany >= 1) {
    receivedCommand = Wire.read();
  }
}

void sendData() {
  switch (receivedCommand) {
    case 1: // Send ID
      Wire.write(ID_HIGH);
      Wire.write(ID_LOW);
      break;
    case 2: { // Send available data size
      uint16_t size = strlen(sensorDataBuffer);
      Wire.write(highByte(size));
      Wire.write(lowByte(size));
      break;
    }
    case 3: // Send actual sensor data
      Wire.write(sensorDataBuffer, strlen(sensorDataBuffer));
      break;
    case 4: // Send device name
      Wire.write(NAME, strlen(NAME));
      break;
    default: // Unknown command
      Wire.write("ERR", 3);
      break;
  }
}
