#include <Arduino.h>
#include <DHT.h>
 
#define DHT22_PIN 7
#define DHTTYPE DHT22
 
DHT DHT22_Sensor(DHT22_PIN, DHTTYPE);
 
void setupDHT22() {
  DHT22_Sensor.begin();
}
 
float readDHT22Temperature() {
  float DHT22_TempC = DHT22_Sensor.readTemperature(); // Read Temperature(°C)

  return DHT22_TempC;
}


float readDHT22Humidity() {
  float DHT22_Humidity = DHT22_Sensor.readHumidity();
  
  return DHT22_Humidity;
 
  delay(1000);
}