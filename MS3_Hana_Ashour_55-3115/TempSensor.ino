#include <ESP8266WiFi.h>
#include <ThingsBoard.h>

#ifndef STASSID
#define STASSID "Salma El Afifi"
#define STAPSK "123456789"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

const char* thingsboardServer = "demo.thingsboard.io";
const char* token = "47K2A78Hc92VsrG1elMG"; // Replace with your ThingsBoard access token


WiFiClient espClient;
ThingsBoard tb(espClient);

const int analogPin = A0;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  tb.connect(thingsboardServer, token);
  
}

void loop() {
  int sensorValue = analogRead(analogPin);
  float temperatureC = sensorValue; // Adjust the conversion factor as needed

  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.println(" °C");

  tb.sendTelemetryFloat("temperature", temperatureC); // Send temperature to ThingsBoard

  delay(10000);
}



