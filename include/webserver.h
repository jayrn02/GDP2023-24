#ifndef webserver_H
#define webserver_H

// Function prototypes
void setupWeb();
void printWifiStatus();
void sendWeb(float phValue, float temperature, float turbidity, float tds, float roomTemp, float humidity);

#endif