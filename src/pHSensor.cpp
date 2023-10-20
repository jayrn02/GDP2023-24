/* 

CODE
The code consists of taking 10 samples of the analog input A0, sort them, and discard the highest and the lowest 
and calculate the average of the six remaining samples converting this value to a voltage in the variable pHVol, 
then using the equation we have calculated with the reference values of pH become pHVol to pHValue 
and it is sent on the serial port to view the article in the serial monitor.

MORE DETAILS, LINK:
https://arduinotech.dk/shop/ph-sensor-module-bnc/
*/

#include <Arduino.h>

const int analogInPin = A0;
int sensorValue = 0;
unsigned long int avgValue;
float b;
int buf[10],temp;

float readPHSensor()   {
    // this should be reading 10 value every 100ms
    for(int i=0;i<10;i++)   {
        buf[i]=analogRead(analogInPin);
        delay(10);
    }
    for(int i=0;i<9;i++)    {
        for(int j=i+1;j<10;j++) {
            if(buf[i]>buf[j])   {
                temp=buf[i];
                buf[i]=buf[j];
                buf[j]=temp;
            }
        }
    }

    avgValue=0;

    for(int i=2;i<8;i++)
        avgValue+=buf[i];

    float pHVol=(float)avgValue*5.0/1024/6;
    float phValue = -5.70 * pHVol + 21.34 + 3.72;

    return phValue;
}
