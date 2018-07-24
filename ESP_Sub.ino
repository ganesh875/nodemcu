/*
   Temperature Monitoring Web Server Connects to your Router
   circuits4you.com
*/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <MQTT.h>

#include "index.h"  //Web page

//SSID and Password of your WiFi router
const char* ssid      = "";
const char* password  = "";

WiFiClient net;
MQTTClient client;

ESP8266WebServer server(80); //Server on port 80


void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!client.connect("arduino", "try", "try")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

  client.subscribe("nodemcu/temprature");
  // client.unsubscribe("/hello");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
  if(payload == "world"){
    digitalWrite(LED_BUILTIN, LOW);
    delay(2000);
    digitalWrite(LED_BUILTIN, HIGH);
  }else{
    digitalWrite(LED_BUILTIN, HIGH);
  }
}

//===============================================================
//     This rutine is exicuted when you open its IP in browser
//===============================================================
void handleRoot() {
  String s = MAIN_page;
  server.send(200, "text/html", s); //Send webpage to browser
}
//===============================================================
//                  SETUP
//===============================================================
void setup(void) {

  Serial.begin(115200);

  dht.begin();
  pinMode(LED_BUILTIN, OUTPUT);
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported by Arduino.
  // You need to set the IP address directly.
  client.begin("broker.shiftr.io", net);
  client.onMessage(messageReceived);
  connect();
  
  server.on("/", handleRoot); //handle root location

  server.begin();                  //Start server
  Serial.println("HTTP server started");
}
//===============================================================
//                     LOOP
//===============================================================
void loop(void) {
  server.handleClient();     //Handle client requests
   client.loop();
  delay(10);  // <- fixes some issues with WiFi stability

  if (!client.connected()) {
    connect();
  }
}
