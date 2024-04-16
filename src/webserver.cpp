#include <Arduino.h>
#include "WiFiS3.h"
#include "arduino_secret.h"

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

float data[6] = {0, 0, 0, 0, 0, 0}; // Do i actually need this? Why is this here??

int status = WL_IDLE_STATUS;

WiFiServer server(80);

void printWifiStatus() {
    // Print the SSID of the network you're attached to:
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    // Print your board's IP address used to access from web:
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);

    // Print the received signal strength:
    long rssi = WiFi.RSSI();
    Serial.print("Signal Strength (RSSI): ");
    Serial.print(rssi);
    Serial.println(" dBm");
}

void setupWeb() {
    // Initialize serial and wait for port to open:
    Serial.begin(9600);
    while (!Serial) {
        ; // Wait for the serial port to connect. Needed for the native USB port only
    }

    // Check for the WiFi module:
    if (WiFi.status() == WL_NO_MODULE) {
        Serial.println("Communication with WiFi module failed!");
        // Don't continue
        while (true);
    }

    String fv = WiFi.firmwareVersion();
    if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
        Serial.println("Please upgrade the firmware");
    }

    // Attempt to connect to the WiFi network: (Will continue to check indefinately, might need to change this to exit if failed to connect after a certain amount of time)
    while (status != WL_CONNECTED) {
        Serial.print("Attempting to connect to SSID: ");
        Serial.println(ssid);
        // Connect to WPA/WPA2 network.
        status = WiFi.begin(ssid, pass);

        // Wait 10 seconds for connection:
        delay(10000);
    }
    server.begin();
    // You're connected now, so print out the status:
    printWifiStatus();
}


void sendWeb(float phValue, float temperature, float turbidity, float tds, float roomTemp, float humidity, int waterLevel, float carbonDioxide) {
    // Listen for incoming clients
    WiFiClient client = server.available();
    if (client) {
        Serial.println("new client");
        // An HTTP request ends with a blank line
        boolean currentLineIsBlank = true;
        while (client.connected()) {
            if (client.available()) {
                char c = client.read();
                Serial.write(c);
                if (c == '\n' && currentLineIsBlank) {
                    // Send a standard HTTP response header
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-Type: text/html");
                    client.println("Connection: close");  // The connection will be closed after completion of the response
                    client.println("Refresh: 2");  // Refresh the page automatically every 2 sec
                    client.println();
                    client.println("<!DOCTYPE HTML>");
                    client.println("<html>");
                    client.println("<head>");
                    client.println("<title>IOT Rainwater Live Sensor</title>");
                    client.println("</head>");

                    client.println("<body>");
                    
                    client.println("<img src='https://cdn.enfsolar.com/ID/logo/5f59c39a063ed.png?v=1'>");
                    client.println("<h1>Water Sensor Data</h1>");

                    client.println("<table border='1' cellpadding='5'>");

                    // Output the value of each analog input pin
                    client.println("<tr>");
                    client.println("<th>pH</th>");
                    client.println("<td>");
                    client.println(phValue);
                    client.println("</td>");
                    client.println("</tr>");

                    // Temperature (water)
                    client.println("<tr>");
                    client.println("<th>Temperature</th>");
                    client.println("<td>");
                    client.println(temperature);
                    client.println("</td>");
                    client.println("</tr>");

                    // TDS
                    client.println("<tr>");
                    client.println("<th>TDS</th>");
                    client.println("<td>");
                    client.println(tds);
                    client.println("</td>");
                    client.println("</tr>");

                    // Turbidity
                    client.println("<tr>");
                    client.println("<th>Turbidity</th>");
                    client.println("<td>");
                    client.println(turbidity);
                    client.println("</td>");
                    client.println("</tr>");

                    // Water Level
                    client.println("<tr>");
                    client.println("<th>Water Level</th>");
                    client.println("<td>");
                    client.println(waterLevel);
                    client.println("</td>");
                    client.println("</tr>");


                    client.println("</table>");  // Close the table


                    client.println("<h1>Tank Sensor Data</h1>");

                    client.println("<table border='1' cellpadding='5'>");

                    // DHT22
                    client.println("<tr>");
                    client.println("<th>Temperature</th>");
                    client.println("<td>");
                    client.println(roomTemp);
                    client.println("</td>");
                    client.println("</tr>");

                    client.println("<tr>");
                    client.println("<th>Humidity</th>");
                    client.println("<td>");
                    client.println(humidity);
                    client.println("</td>");
                    client.println("</tr>");
                    client.println("</table>");  // Close the table

                    client.println("<tr>");
                    client.println("<th>Carbon Dioxide</th>");
                    client.println("<td>");
                    client.println(carbonDioxide);
                    client.println("</td>");
                    client.println("</tr>");
                    client.println("</table>");  // Close the table


                    client.println("</body>");
                    client.println("</html>");
                    break;
                }
                if (c == '\n') {
                    // You're starting a new line
                    currentLineIsBlank = true;
                } else if (c != '\r') {
                    // You've gotten a character on the current line
                    currentLineIsBlank = false;
                }
            }
        }
        delay(1);   // Give the web browser time to receive the data
        // Close the connection:
        client.stop();
        Serial.println("client disconnected");
    }
}
