#include <Arduino.h>

int floatSwitchPin = 8;  // The pin where the float switch is connected
int waterLevelStatus = LOW; // Variable to store the water level status

int checkWaterLevel() {
  waterLevelStatus = digitalRead(floatSwitchPin); // Read the water level status from the float switch
  
  if (waterLevelStatus == HIGH) {
    return 1;
  } else {
    return 0;
  }
}