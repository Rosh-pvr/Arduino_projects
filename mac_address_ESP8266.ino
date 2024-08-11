#include <ESP8266WiFi.h>  // Include the WiFi library for ESP8266

void setup() {
  Serial.begin(115200);  // Start the Serial communication at 115200 baud rate

  // Wait for the serial connection to be established
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // Retrieve the MAC address of the ESP8266
  String macAddress = WiFi.macAddress();

  // Print the MAC address to the Serial Monitor
  Serial.println("ESP8266 MAC Address: " + macAddress);
}

void loop() {
  // Nothing to do here
}
