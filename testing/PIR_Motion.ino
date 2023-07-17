#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

// Function Prototypes
void sendData(String fieldUri, int sensorValue);
void showData(const char* title, int value, const char* unit);

//  Pin Setup
const int roomTempPin = A1;
const int stoveTempPin = A3;
const int pirPin = 6;
const int ultraPin = A4;
const int canisterPin = A5;
const int gasPin = A3;



String ssid = "Simulator Wifi";
String password = "";
String host = "api.thingspeak.com";
const int httpPort = 80;
String uri1 = "/update?api_key=TU5KKYIPQOS8STCY&field1=";
String uri2 = "/update?api_key=TU5KKYIPQOS8STCY&field2=";
String uri3 = "/update?api_key=TU5KKYIPQOS8STCY&field3=";
String uri4 = "/update?api_key=TU5KKYIPQOS8STCY&field3=";
String uri5 = "/update?api_key=TU5KKYIPQOS8STCY&field3=";
String uri6 = "/update?api_key=TU5KKYIPQOS8STCY&field3=";

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


/*
    ......................
    .......Setting........
    ......................
*/
// PIR Detection
int motionState = LOW;
unsigned long motionStartTime = 0;
unsigned long noMotionStartTime = 0;
const unsigned long motionDuration = 1000;
const unsigned long noMotionDuration = 1000;
int previousMotionState = -1;




void setupESP8266() {
  Serial.begin(115200);
  delay(100);
  
  Serial.println("AT");
  delay(100);
  if (!Serial.find("OK")) {
    Serial.println("Failed to connect to ESP8266");
    while (1) continue;
  }
  
  Serial.println("AT+CWJAP=\"" + ssid + "\",\"" + password + "\"");
  delay(100);
  if (!Serial.find("OK")) {
    Serial.println("Failed to connect to WiFi");
    while (1) continue;
  }
}

void sendData(String fieldUris[], int sensorValues[]) {
  String httpRequest = "GET ";

  // Add all the fields to the HTTP request
  for (int i = 0; i < 5; i++) {
    httpRequest += fieldUris[i] + String(sensorValues[i]);
    if (i < numFields - 1) {
      httpRequest += "&";
    }
  }

  httpRequest += " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n";

  int contentLength = httpRequest.length();

  Serial.print("AT+CIPSEND=");
  Serial.println(contentLength);
  delay(100);
  if (!Serial.find(">")) {
    Serial.println("Failed to send HTTP request length");
    return;
  }

  Serial.print(httpRequest);
  delay(100);
  if (!Serial.find("SEND OK\r\n")) {
    Serial.println("Failed to send HTTP request");
    return;
  }

  delay(500);

  // Wait for response from the ESP8266
  while (!Serial.available()) {
    delay(10);
  }

  // Read and discard the response from the ESP8266
  while (Serial.available()) {
    Serial.read();
  }
}




void showData(const char* title, int value, const char* unit) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(title);
  lcd.setCursor(0, 1);
  lcd.print(value);
  lcd.print(unit);
  delay(1000);
}

/*
    ......................
    .......Sensors........
    ......................
*/


//  PIR (Human Detection)
void detectMotion() {   
  int currentMotionState = digitalRead(pirPin);

  if (currentMotionState == HIGH && motionState == LOW) {
    motionStartTime = millis();
    motionState = HIGH;
  }
  else if (currentMotionState == LOW && motionState == HIGH) {
    noMotionStartTime = millis();
    motionState = LOW;
  }

  if (motionState == HIGH && (millis() - motionStartTime >= motionDuration)) {
    showData("PIR Motion", 1, "");

    if (motionState != previousMotionState) {
      sendData(uri3, 1);
      previousMotionState = motionState;
    }
  }
  else if (motionState == LOW && (millis() - noMotionStartTime >= noMotionDuration)) {
    showData("PIR Motion", 0, "");

    if (motionState != previousMotionState) {
      sendData(uri3, 0);
      previousMotionState = motionState;
    }
  }
}

//  Force (Canister Quantity)
void detectCanister() {
  int max = 0;
  int min = 0

}


void detectRoomTemp() {

}


void detectStoveTemp()  {

}


void detectPot()  {

}



void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(pirPin, INPUT);
  setupESP8266();
  showData("PIR Motion", 0, "");
  Serial.println("AT+CIPSTART=\"TCP\",\"" + host + "\"," + httpPort);
  delay(5000);
  if (!Serial.find("OK")) {
    Serial.println("Failed to establish connection with server");
    return;
  }
}

void loop() {

  //  Read from Sensors
  int roomTempValue = analogRead(tempPin);
  int stoveTempValue = analogRead();
  int pirValue = digitalRead(pirPin);
  int ultraValue = analogRead();
  int canisterValue = analogRead();
  int gasValue = analogRead(lightPin);
  

  detectMotion();

  int sensorValues[] = {roomTempValue, stoveTempValue, pirValue, ultraValue, canisterValue, gasValue};
  String fieldUrls[] = {"/field1=", "/field2=", "/field3=", "/field4=", "/field5=", "/field6="};
  sendData(fieldUrls, sensorValues)
  delay(30000)


 
}
