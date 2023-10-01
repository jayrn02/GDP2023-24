#include <Arduino.h>
#include "TurbiditySensor.h"

int setupTurbiditySensor() {
    pinMode(A5, INPUT);
}

float readTurbidity() {
    int sensorValue = analogRead(A2);
    float turbidity = sensorValue;
    // float turbidity = map(sensorValue, 0, 640, 100, 0); 
    return turbidity;
}