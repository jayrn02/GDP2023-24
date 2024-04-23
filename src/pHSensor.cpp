#include <Arduino.h>

const int analogInPin = A0; // Pin where the pH sensor output is connected
int sensorValue = 0;
unsigned long int avgValue;
float b;
int buf[10], temp;

// Obtained voltage and pH referecne values
float V_686 = 3.2690; 
float V_401 = 3.6572; 

float pH1 = 6.86;
float pH2 = 4.01;

// Calculate the slope gradiend
float slope = (pH2 - pH1) / (V_401 - V_686);

// Calculate the intercept
float intercept = pH1 - (slope * V_686);


float readPHSensor() {
    for(int i = 0; i < 10; i++) {
        buf[i] = analogRead(analogInPin);
        delay(10);
    }
    for(int i = 0; i < 9; i++) {
        for(int j = i + 1; j < 10; j++) {
            if(buf[i] > buf[j]) {
                temp = buf[i];
                buf[i] = buf[j];
                buf[j] = temp;
            }
        }
    }

    avgValue = 0;
    for(int i = 2; i < 8; i++) {  // Average the middle six values
        avgValue += buf[i];
    }

    float pHVol = (float)avgValue * 5.0 / 1024 / 6; // Convert ADC value to voltage
    float phValue = slope * pHVol + intercept; // Calculate pH using the calibrated slope and intercept

    return phValue;
}

