#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

LiquidCrystal_I2C lcd(0x27, 2, 1); // Set the LCD address and pins

// Your variables to display



void setupLCD() {

    lcd.begin(16, 2); // Initialize the LCD
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("IOT Rainwater Sensor");
    delay(5000);
    lcd.clear();
}

void displayLCD(char* var) {
    lcd.setCursor(0, 0);
    lcd.print("Variable: ");
    lcd.print(var);

    delay(2000); // Adjust this value to change the display time

    lcd.clear();
}