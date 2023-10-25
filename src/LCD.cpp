#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address and pins

// Your variables to display

void setupLCD() {
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("IOT Rainwater");
    lcd.setCursor(0, 1);
    lcd.print("Sensor :D");
    delay(5000);
    lcd.clear();
}

void displayLCD(float var) {
    lcd.setCursor(0, 0);
    lcd.print("Variable: ");
    lcd.print(var);

    delay(2000); // Adjust this value to change the display time

    lcd.clear();
}