#include <WiFiS3.h>
#include "arduino_secret.h"
#include <ThingSpeak.h>

const char* ssid1 = SECRET_SSID;
const char* password = SECRET_PASS;
unsigned long channelID = atol(SECRET_CHANNEL);
const char* writeAPIKey = SECRET_API;
WiFiClient client;

void setupThingSpeak() {
  WiFi.begin(ssid1, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
}

void sendData(float phValue, float temperature, float turbidity, float tds, float roomTemp, float humidity, int waterLevel) {

  // Initialize ThingSpeak
  ThingSpeak.begin(client);

  // Send temperature to ThingSpeak

  ThingSpeak.setField(1, phValue);
  ThingSpeak.setField(2, temperature);
  ThingSpeak.setField(3, turbidity);
  ThingSpeak.setField(4, tds);
  ThingSpeak.setField(5, roomTemp);
  ThingSpeak.setField(6, humidity);
  ThingSpeak.setField(7, waterLevel);

  int x = ThingSpeak.writeFields(channelID, writeAPIKey);
}