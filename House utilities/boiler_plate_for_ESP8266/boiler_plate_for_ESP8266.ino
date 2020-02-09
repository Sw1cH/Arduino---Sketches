//This boiler plate code will be a part of every ESP8266 sketch we write. This code does the following:
//
//- Includes the ESP8266 library ESP8266WiFi.h.
//- Creates the instance "server" of the class "WiFiServer" listening on port 80. Notice "server" is a global instance. 
//- Set the mode of our ESP8266 to be an Access Point (AP).
//- Provide the SSID and password. The password / passphrase has to be at least 8 characters long.
//
//- Fire-up our server by calling the begin() method.
//



#include <ESP8266WiFi.h>

WiFiServer server(80); //Initialize the server on Port 80

void setup() {

WiFi.mode(WIFI_AP); //Our ESP8266-12E is an AccessPoint 
WiFi.softAP("Hello_IoT", "12345678"); // Provide the (SSID, password); . 
server.begin(); // Start the HTTP Server

}

void loop() { }
