#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include "image.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setupOLED() {
  // Serial communication setup
  display.clearDisplay();
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // OLED initialization
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  display.clearDisplay();
}

void bootDisplay()  {
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  
  display.drawBitmap(0, 0, myImage, 128, 64, 1);
  display.display();
  delay(2000);
  display.clearDisplay();


  display.println("IOT\nRainwater\nMonitoring");
  display.display();
  delay(2000);
}

void displayOLED(float pH, float temperature, float turbidity, float tds, float roomTemp, float humidity) {

  display.clearDisplay();
  
  // Display setup
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);

  // Display Water Property
  display.print("pH: ");
  display.println(pH);

  display.print("W Temp: ");
  display.print(temperature);
  display.println(" C");

  display.print("Turbidity: ");
  display.println(turbidity);

  display.print("TDS: ");
  display.print(tds);
  display.println(" ppm");


  // Display Water Property
  //display.println("Room Property");
  display.print("Temp: ");
  display.print(roomTemp);
  display.println(" C");
  display.print("Humidity: ");
  display.print(humidity);
  display.println(" %");

  display.display();
}
