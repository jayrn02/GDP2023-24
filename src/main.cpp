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


  if (waterLevel == 1) {
    matrix.loadFrame(chip);
  } else {
    matrix.loadFrame(fullOn);
  }

  // Physical interface output
  displayOLED(phValue, temperature, turbidity, tds, roomTemp, humidity);
  //displayLCD(temperature);
  
    sendWeb(phValue, temperature, turbidity, tds, roomTemp, humidity, waterLevel);

  // send data every 8 loop
  thingSpeakLoop += 1;
  if (thingSpeakLoop == 8)  {
    sendData(phValue, temperature, turbidity, tds, roomTemp, humidity, waterLevel);
    thingSpeakLoop = 0;
  }
  delay(2000);
}