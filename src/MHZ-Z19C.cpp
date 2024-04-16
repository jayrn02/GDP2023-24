#include <SoftwareSerial.h>
#include <Arduino.h>

// RX and TX pins connected to the sensor's TX and RX respectively
SoftwareSerial co2Serial(10, 11); // RX, TX

void setupCO2() {
  Serial.begin(9600);
  co2Serial.begin(9600);
  Serial.println("MH-Z19C CO2 sensor test");
}

float getCO2() {
  // Send command to get CO2 readings
  unsigned char cmd[9] = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};
  co2Serial.write(cmd, 9);

  // Wait for the sensor to respond
  delay(100);

  // Read response from the sensor
  if (co2Serial.available() >= 9) {
    unsigned char response[9];
    co2Serial.readBytes(response, 9);
    
    // Calculate CO2 concentration from the response
    int high = response[2];
    int low = response[3];
    float co2ppm = high * 256 + low;
    
    return co2ppm;
  }

  // Return a default value or error code if no data is received
  return -1;  // Return -1 to indicate an error in reading data
}
