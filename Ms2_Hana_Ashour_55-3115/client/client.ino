#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#ifndef STASSID
#define STASSID "Hana's phone"
#define STAPSK "bngh5768"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

const char* host = "192.168.201.187";
const uint16_t port = 5608;

ESP8266WiFiMulti WiFiMulti;

// Analog temperature sensor configuration
const int analogPin = A0;

void setup() {
  Serial.begin(115200);

  // We start by connecting to a WiFi network
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);

  Serial.println();
  Serial.println();
  Serial.print("Wait for WiFi... ");

  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  delay(500);
}

void loop() {

  // Read analog voltage from the temperature sensor
  int sensorValue = analogRead(analogPin);

  // Convert the analog value to temperature (adjust the conversion factor as needed)
  float temperatureC = (sensorValue);

  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.println(" °C");

  Serial.print("connecting to ");
  Serial.print(host);
  Serial.print(':');
  Serial.println(port);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;

  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    Serial.println("wait 5 sec...");
    delay(5000);
    return;
  }
  while(true){
  String temperatureString = String(temperatureC, 2);  // Convert temperature to string
  String message =  temperatureString + " °C";
  client.println(message);
  delay(10000);

  }

 
  

  // read back one line from the server
  Serial.println("receiving from remote server");
  String line = client.readStringUntil('\r');
  Serial.println(line);
}

  
  


