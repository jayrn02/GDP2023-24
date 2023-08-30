// Temperatur Sensor for DS18B20 (Digital)

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "DS18B20Sensor.h"

// Pins
#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setupDS18B20Sensor()   {
    sensors.begin();
}

float readTemperatureFromDS18B20()  {

}