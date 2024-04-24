#include <Arduino.h>

//  Library Sensor
#include "DS18B20Sensor.h"
#include "TDSSensor.h"
#include "TurbiditySensor.h"
#include "pHSensor.h"
#include "DHT22Sensor.h"
#include "waterLevel.h"

// Library Others
#include "webserver.h"
#include "OLED.h"
#include "myThingSpeak.h"


#include "Arduino_LED_Matrix.h"
#include "frames.h"   

ArduinoLEDMatrix matrix;
//#include "ArduinoGraphics.h"
//#include "LCD.h"

int thingSpeakLoop = 0;
float accTemperature = 0;
float accPhValue = 0;
float accTurbidity = 0;
float accTds = 0;
float accRoomTemp = 0;
float accHumidity = 0;
int accWaterLevel = 0;

void setup() {
  setupOLED();
  bootDisplay();
  setupDS18B20Sensor();
  setupTDSSensor();
  setupDHT22();
  //setupLCD()
  setupWeb();
  Serial.begin(9600);
  pinMode(8, INPUT_PULLUP);  // Set the float switch pin as input with internal pull-up resistor
  


}

void loop() {
  // Gather Data
  float temperature = readTemperatureFromDS18B20();
  float phValue = readPHSensor();
  float turbidity = readTurbidity();
  float tds = readTDSSensor(temperature);
  
  float roomTemp = readDHT22Temperature();
  float humidity = readDHT22Humidity();

  int checkWaterLevel(); // Declare the function checkWaterLevel()

  int waterLevel = checkWaterLevel();
  

  // Check if water has reached the sensor level
  


  //Serial display output for Debugging
  {
    Serial.println("--------------------\n");

    //  pH
    Serial.print("pH Value = ");
    Serial.println(phValue);

    //  Temp (water)
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");

    //  TDS
    Serial.print("TDS: ");
    Serial.println(tds);

    //  Turbidity
    Serial.print("Turbidity: ");
    Serial.println(turbidity);

    // DHT22
    Serial.print("Temperature: ");
    Serial.println(roomTemp);

    Serial.print("Humidity: ");
    Serial.println(humidity);

    Serial.print("Water Level: ");
    Serial.println(waterLevel);

  }

  accTemperature += temperature;
  accPhValue += phValue;
  accTurbidity += turbidity;
  accTds += tds;
  accRoomTemp += roomTemp;
  accHumidity += humidity;
  accWaterLevel += waterLevel;

  // Physical interface output
  displayOLED(phValue, temperature, turbidity, tds, roomTemp, humidity);
  //displayLCD(temperature);
  
    sendWeb(phValue, temperature, turbidity, tds, roomTemp, humidity, waterLevel);

  // send data every 8 loop
  thingSpeakLoop += 1;
  if (thingSpeakLoop == 8) {
    // Calculate averages
    float avgTemperature = accTemperature / 8;
    float avgPhValue = accPhValue / 8;
    float avgTurbidity = accTurbidity / 8;
    float avgTds = accTds / 8;
    float avgRoomTemp = accRoomTemp / 8;
    float avgHumidity = accHumidity / 8;
    float avgWaterLevel = (float)accWaterLevel / 8;  // Cast to float to calculate average

    // Send average data
    sendData(avgPhValue, avgTemperature, avgTurbidity, avgTds, avgRoomTemp, avgHumidity, avgWaterLevel);

    // Reset accumulators and loop counter
    accTemperature = 0;
    accPhValue = 0;
    accTurbidity = 0;
    accTds = 0;
    accRoomTemp = 0;
    accHumidity = 0;
    accWaterLevel = 0;
    thingSpeakLoop = 0;
  }
  delay(2000);
}