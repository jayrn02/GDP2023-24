#ifndef myThingSpeak_H
#define myThingSpeak_H

void setupThingSpeak();
void sendData(float phValue, float temperature, float turbidity, float tds, float roomTemp, float humidity, int waterLevel);

#endif