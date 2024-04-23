#include <Arduino.h>
#include "TurbiditySensor.h"

int turbidityPin = A2;  

// Define sensor range
int sensorValueLow = 10;  
int sensorValueHigh = 980;


float readTurbidity() {
  int sum = 0; // Sum of the sensor values
  int averageSensorValue = 0; // Average of the sensor values
  
  // Collect 10 readings
  for (int i = 0; i < 10; i++) {
    int sensorValue = analogRead(turbidityPin);  // Read the sensor value

    // Cap the sensor value at 980
    if (sensorValue > 980) {
      sensorValue = 980;
    }

    sum += sensorValue; // Add the capped value to sum
    delay(100); // Short delay between readings for stability
  }

  averageSensorValue = sum / 10; // Calculate average

  // Calculate NTU based on the linear mapping from averageSensorValue to NTU scale
  // Assuming NTU should be 0 at sensorValueHigh and max at sensorValueLow
  float ntu = map(averageSensorValue, sensorValueLow, sensorValueHigh, 4000, 0);

  // Print the average turbidity value in NTU
  
  return ntu;
}