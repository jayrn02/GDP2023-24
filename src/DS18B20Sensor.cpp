// Temperatur Sensor for DS18B20 (Digital)
#include <Arduino.h>
#include "DS18B20Sensor.h"
#include <OneWire.h>
#include <DallasTemperature.h>

// Pins (Digital)
#define ONE_WIRE_BUS 4  // To be changes later

// Acccess Library, I honestly dk whats this
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setupDS18B20Sensor()   {   // Initialize sensors
    sensors.begin();
}

float readTemperatureFromDS18B20()  {
    sensors.requestTemperatures();  // Send the command to get temperature readings
    float temperatureC = sensors.getTempCByIndex(0);    // Read temperature in Celsius
    return temperatureC;
}