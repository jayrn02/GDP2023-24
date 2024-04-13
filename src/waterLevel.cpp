#include <Arduino.h>

const int digitalInPin = 8;

int checkWaterLevel() {
  int waterLevel = digitalRead(digitalInPin);

  if (waterLevel == 1) {
    return 1;
  } else {
    return 0;
  }
}