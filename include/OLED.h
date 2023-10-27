#ifndef OLED_H
#define OLED_H

void setupOLED();
void displayOLED(float phValue, float temperature, float turbidity, float tds, float roomTemp, float humidity);

void bootDisplay();
#endif