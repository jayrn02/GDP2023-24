#include <MHZ.h>
#include <Arduino.h>
#include <SoftwareSerial.h>

#include <SoftwareSerial.h>

// RX and TX pins connected to the sensor's TX and RX respectively
SoftwareSerial co2Serial(10, 11); // RX, TX

void setupCO2() {
  // Start the serial communication with the computer and the sensor
  co2Serial.begin(9600);
  Serial.println("MH-Z19C CO2 sensor test");
}

float getCO2() {
  // Send command to get CO2 readings
  unsigned char cmd[9] = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};
  co2Serial.write(cmd, 9);

  // Wait for the sensor to respond
  delay(1000);

  // Read response from the sensor
  if (co2Serial.available()) {
    unsigned char response[9];
    co2Serial.readBytes(response, 9);
    
    // Calculate CO2 concentration from the response
    int high = response[2];
    int low = response[3];
    int co2ppm = high * 256 + low;
    
    // Print the CO2 concentration
    Serial.print("CO2 Concentration: ");
    Serial.print(co2ppm);
    Serial.println(" ppm");


    return co2ppm;
  }

  // Wait a bit before reading again
  delay(2000);
}


