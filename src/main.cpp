#include <Arduino.h>

//  Library Sensor
#include "DS18B20Sensor.h"
#include "TDSSensor.h"
#include "TurbiditySensor.h"
#include "pHSensor.h"
#include "DHT22Sensor.h"

// Library Others?
#include "webserver.h"
#include "OLED.h"
#include "myThingSpeak.h"

//#include "ArduinoGraphics.h"
//#include "Arduino_LED_Matrix.h"
//#include "LCD.h"

int thingSpeakLoop = 0;

void setup() {
  // Initialize the built-in LED pin as an output
  
  setupOLED();
  bootDisplay();
  setupDS18B20Sensor();
  setupTDSSensor();
  setupDHT22();
  //setupLCD()
  setupWeb();
  Serial.begin(9600);
}

void loop() {
  // Gather Data
  float phValue = readPHSensor();
  float temperature = readTemperatureFromDS18B20();
  float tds = readTDSSensor(temperature);
  float roomTemp = readDHT22Temperature();
  float humidity = readDHT22Humidity();
  float turbidity = readTurbidity();

  //Serial display output
  {
    Serial.println("--------------------\n");

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

    //  Turbidity
    Serial.print("Turbidity: ");
    Serial.println(turbidity);

    // DHT22
    Serial.print("Temperature: ");
    Serial.println(roomTemp);

    Serial.print("Humidity: ");
    Serial.println(humidity);
  }
  // Physical interface output
  displayOLED(phValue, temperature, turbidity, tds, roomTemp, humidity);
  //displayLCD(temperature);
  
    sendWeb(phValue, temperature, turbidity, tds, roomTemp, humidity);

  // send data every 8 loop
  thingSpeakLoop += 1;
  if (thingSpeakLoop == 8)  {
    sendData(phValue, temperature, turbidity, tds, roomTemp, humidity);
    thingSpeakLoop = 0;
  }
  

  delay(2000);
}