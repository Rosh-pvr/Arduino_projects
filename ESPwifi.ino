#include <ESP8266WiFi.h>

// Replace with your network credentials
const char* ssid = "RAMAKRISHNA";
const char* password = "roshan18";

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Connecting to Wi-Fi...");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Your code here
}
