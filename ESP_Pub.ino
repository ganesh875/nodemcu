#include <ESP8266WiFi.h>
#include <MQTTClient.h>
#include "DHT.h"

#define DHTPIN 2 
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

const char* ssid     = "";
const char* password = "";

WiFiClient WiFiclient;
MQTTClient client;

unsigned long lastMillis = 0;

void setup() {
 dht.begin();
 Serial.begin(115200);
 delay(10);
 Serial.println();
 Serial.println();
 Serial.print("Connecting to ");
 Serial.println(ssid);

 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
   delay(500);
   Serial.print(".");
 }

 Serial.println("");
 Serial.println("WiFi connected");  
 Serial.println("IP address: ");
 Serial.println(WiFi.localIP());
 delay(2000);
 
 Serial.print("connecting to MQTT broker...");
 client.begin("broker.shiftr.io", WiFiclient); //
 connect();
}

void connect() {
 while (!client.connect("nodemcu", "try", "try")) {
   Serial.print(".");
 }

 Serial.println("\nconnected!");
// client.subscribe("/hello");
}

void loop() {
 float Temp = dht.readTemperature();
 client.loop();
 if(!client.connected()) {
   connect();
 }

 if(millis() - lastMillis > 1000) {
   lastMillis = millis();
   client.publish("nodemcu/temprature", (String)Temp);
 }
}
