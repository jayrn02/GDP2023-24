// Temperatur Sensor for DS18B20 (Digital)
#include <Arduino.h>
#include "DS18B20Sensor.h"
#include <DallasTemperature.h>
#include <OneWire.h>

// Pins (Digital)
#define ONE_WIRE_BUS 2  // To be changes later

// Acccess Library,
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setupDS18B20Sensor()   {   // Initialize sensors
    sensors.begin();
}

float readTemperatureFromDS18B20()  {
    sensors.requestTemperatures();  // Send the command to get temperature readings
    return sensors.getTempCByIndex(0);
}