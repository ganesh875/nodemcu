#include <ESP8266WiFi.h>

const char* ssid     = "" ;// enter SSID of your wifi network
const char* password = ""; // enter password of your wifi network
 
const char* host = "192.168.XX.XX"; // enter your host ip address
const char* streamId   = "collectdata.php";
 
void sendRequest(String mood){
  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
  }
  
  // We now create a URI for the request
  String url = "/";
  url += streamId;
  url += "?mood=";
  url += mood;
 
 Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
              "Connection: close\r\n\r\n");
  delay(10);
  Serial.println();
  Serial.println("closing connection");
 
  delay(2500);
  }
 
void setup() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network
 
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
//  digitalWrite(blue,HIGH);
}
 
void loop() {
  
  for(int i = 0;i<=2;i++)
  {
    if(i==0){
      sendRequest("Happy");
      }
      else if(i ==1){
        sendRequest("Sad");
        }else if (i ==2){
          sendRequest("Angry");
          }
      delay(10000);
  }
}
