#include <Arduino.h>
#include "DS18B20Sensor.h"
#include "TDSSensor.h"
#include "TurbiditySensor.h"
#include "pHSensor.h"
#include "DHT22Sensor.h"

void setup() {
  // Initialize the built-in LED pin as an output
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  
  setupDS18B20Sensor();
  setupTDSSensor();
  setupTurbiditySensor();
  setupDHT22();
}

void loop() {
  //  pH
  float phValue = readPHSensor();

  Serial.print("pH Value = ");
  Serial.println(phValue);


  //  Temp
  float temperature = readTemperatureFromDS18B20();
  
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C"); // Print temperature with a newline character
  

  //  TDS
  float tds = readTDSSensor(temperature);

  Serial.print("TDS: ");
  Serial.println(tds);


  //  Turbidity
  float turbidity = readTurbidity();

  Serial.print("Turbidity: ");
  Serial.println(turbidity);


  // DHT22
  float roomTemp = readDHT22Temperature();
  float humidity = readDHT22Humidity();


  Serial.print("Temperature: ");
  Serial.println(roomTemp);

  Serial.print("Humidity: ");
  Serial.println(humidity);
  


  Serial.println("--------------------\n");
  delay(2000); 
}