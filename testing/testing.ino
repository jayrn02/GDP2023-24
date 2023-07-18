#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

// Function Prototypes
void sendData(String fieldUris[], int sensorValues[], int numFields);
void showData(const char* title, int value, const char* unit);

// Pin Setup
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

String fieldUris[6] = {"/update?api_key=TU5KKYIPQOS8STCY&field1=",
                       "/update?api_key=TU5KKYIPQOS8STCY&field2=",
                       "/update?api_key=TU5KKYIPQOS8STCY&field3=",
                       "/update?api_key=TU5KKYIPQOS8STCY&field4=",
                       "/update?api_key=TU5KKYIPQOS8STCY&field5=",
                       "/update?api_key=TU5KKYIPQOS8STCY&field6="};

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

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
      pirValue = 1; //Detected
      previousMotionState = motionState;
    }
  }
  else if (motionState == LOW && (millis() - noMotionStartTime >= noMotionDuration)) {
    showData("PIR Motion", 0, "");

    if (motionState != previousMotionState) {
      pirValue = 0; //Not Detected
      previousMotionState = motionState;
    }
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

void detectMotion() {   
  // ... Your motion detection code ...
}

void detectCanister() {
  int canisterValue = analogRead(canisterPin);
  // Map the analog read value from 0-1023 to 0-100
  canisterValue = map(canisterValue, 0, 1023, 0, 100);
  showData("Canister", canisterValue, "%");
}

void detectRoomTemp() {
  int roomTempValue = analogRead(roomTempPin);
  // Convert the analog read value to temperature (Depends on the sensor used)
  // Here, an example conversion is shown. Adjust according to your sensor's data sheet.
  roomTempValue = roomTempValue * 0.48828125;
  showData("Room Temp", roomTempValue, "C");
}

void detectStoveTemp()  {
  int stoveTempValue = analogRead(stoveTempPin);
  // Convert the analog read value to temperature
  stoveTempValue = stoveTempValue * 0.48828125;
  showData("Stove Temp", stoveTempValue, "C");
}

void detectPot()  {
  int ultraValue = analogRead(ultraPin);
  // Here an example conversion is shown. Adjust according to your sensor's data sheet.
  ultraValue = ultraValue * 0.48828125;
  showData("Pot", ultraValue, "cm");
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

void loop() {
  // Read from Sensors
  int roomTempValue = analogRead(roomTempPin);
  int stoveTempValue = analogRead(stoveTempPin);
  int pirValue = digitalRead(pirPin);
  int ultraValue = analogRead(ultraPin);
  int canisterValue = analogRead(canisterPin);
  int gasValue = analogRead(gasPin);

  detectMotion();
  detectRoomTemp();
  detectStoveTemp();
  detectPot();
  detectCanister();

  int sensorValues[] = {roomTempValue, stoveTempValue, pirValue, ultraValue, canisterValue, gasValue};
  sendData(fieldUris, sensorValues, 6);
  delay(30000); // Delay of 30 seconds
}









void sendData(String fieldUri, int sensorValue) {
  String httpRequest = "GET " + fieldUri + String(sensorValue) + " HTTP/1.1\r\n" +
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
 