#include <Arduino.h>
#include "DS18B20Sensor.h"
#include "TDSSensor.h"
#include "TurbiditySensor.h"

void setup() {
  // Initialize the built-in LED pin as an output
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  
  setupDS18B20Sensor();
  setupTDSSensor();
  setupTurbiditySensor();
}

void loop() {

  //  Temp
  float temp = readTemperatureFromDS18B20();
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println(" °C"); // Print temperature with a newline character
  

  //  TDS
  float tds = readTDSSensor();

  Serial.print("TDS: ");
  Serial.println(tds);


  //  Turbidity
  float turbidity = readTurbidity();

  Serial.print("Turbidity: ");
  Serial.println(turbidity);

  Serial.println("--------------------");

  delay(2000); 
}