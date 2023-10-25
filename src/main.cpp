#include <Arduino.h>
#include "DS18B20Sensor.h"
#include "TDSSensor.h"
#include "TurbiditySensor.h"
#include "pHSensor.h"
#include "DHT22Sensor.h"
#include "LCD.h"
#include "OLED.h"


void setup() {
  // Initialize the built-in LED pin as an output
  Serial.begin(9600);
  

  setupDS18B20Sensor();
  setupTDSSensor();
  //setupTurbiditySensor();
  setupDHT22();
  setupLCD();
  setupOLED();
}

void loop() {
  
  // Gather Data First
  float phValue = readPHSensor();
  float temperature = readTemperatureFromDS18B20();
  float tds = readTDSSensor(temperature);
  float roomTemp = readDHT22Temperature();
  float humidity = readDHT22Humidity();

  //  pH
  Serial.print("pH Value = ");
  Serial.println(phValue);

  //  Temp (water)
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C"); // Print temperature with a newline character
  

  //  TDS
  

  Serial.print("TDS: ");
  Serial.println(tds);

/*
  //  Turbidity
  float turbidity = readTurbidity();

  Serial.print("Turbidity: ");
  Serial.println(turbidity);

*/
  // DHT22



  Serial.print("Temperature: ");
  Serial.println(roomTemp);

  Serial.print("Humidity: ");
  Serial.println(humidity);
  

  Serial.println("--------------------\n");
  //displayLCD(temperature);
  
  displayOLED(phValue);

  delay(2000);
  
}