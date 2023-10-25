#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setupOLED() {
  // Serial communication setup
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // OLED initialization
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();
}

void displayOLED(float pH) {


display.clearDisplay();
  // Display setup
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);

  // Display the data you want to show
  display.print("pH: ");
  display.println(pH);
  display.println("Stuff1: ");
  display.println("Stuff2: ");
  display.println("Room Property");
  display.print("Temperature: ");
  display.print("Humidity: ");
  display.display();
}
