#include <Arduino.h>
#include <DS18B20Sensor.h>

void setup() {
  // Initialize the built-in LED pin as an output
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  setupDS18B20Sensor();
}

void loop() {
  // Turn the LED on
  float temp = readTemperatureFromDS18B20();
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println(" °C"); // Print temperature with a newline character
  delay(1000); // Delay for one second (adjust as needed)
}