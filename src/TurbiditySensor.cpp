#include <Arduino.h>
#include "TurbiditySensor.h"

float readTurbidity() {
  int sensorValue = analogRead(A2);
  float voltage = sensorValue; // * (5.0 / 1024.0); / / Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  
  return voltage;
}