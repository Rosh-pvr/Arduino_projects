

#include <SoftwareSerial.h>
#include <ModbusMaster.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Define OLED display size
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// RS-485 Modbus setup
#define RS485_DE 7 // DE pin
#define RS485_RE 8 // RE pin
#define RS485_TX 10 // TX pin for SoftwareSerial
#define RS485_RX 11 // RX pin for SoftwareSerial

SoftwareSerial rs485Serial(RS485_RX, RS485_TX);
ModbusMaster node;

// Soil moisture sensor pins
#define SOIL_ANALOG_PIN A0  // Analog pin for soil moisture
#define SOIL_DIGITAL_PIN 2  // Digital pin for soil moisture

// Soil moisture threshold for wet/dry condition
const int MOISTURE_THRESHOLD = 600;

void preTransmission() {
  digitalWrite(RS485_DE, HIGH); // Enable RS-485 transmit mode
  digitalWrite(RS485_RE, LOW);  // Disable RS-485 receive mode
}

void postTransmission() {
  digitalWrite(RS485_DE, LOW);  // Disable RS-485 transmit mode
  digitalWrite(RS485_RE, HIGH); // Enable RS-485 receive mode
}

void setup() {
  Serial.begin(9600); // Initialize serial communication for debugging

  // Initialize SoftwareSerial for RS-485
  rs485Serial.begin(9600);
  node.begin(1, rs485Serial); // Slave ID 1 (check your NPK sensor manual)
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);

  // Initialize RS-485 pins
  pinMode(RS485_DE, OUTPUT);
  pinMode(RS485_RE, OUTPUT);
  digitalWrite(RS485_DE, LOW); // Default to receive mode
  digitalWrite(RS485_RE, HIGH);

  // Initialize OLED
  if (!display.begin(0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // Set soil sensor digital pin as input
  pinMode(SOIL_DIGITAL_PIN, INPUT);
}

void loop() {
  // ** Soil Moisture Sensor **
  int soilAnalogValue = analogRead(SOIL_ANALOG_PIN); // Analog value
  int soilDigitalValue = digitalRead(SOIL_DIGITAL_PIN); // Digital value
  int moisturePercentage = map(soilAnalogValue, 1023, 0, 0, 100); // Map to percentage
  String soilCondition = (moisturePercentage > 50) ? "Dry" : "Wet";

  // ** NPK Sensor via RS-485 **
  uint8_t result;
  uint16_t data[3]; // Array to store NPK values (Nitrogen, Phosphorus, Potassium)

  // Send Modbus request to read holding registers
  result = node.readHoldingRegisters(0x0000, 3); // Address 0x0000, 3 registers for NPK
  if (result == node.ku8MBSuccess) {
    data[0] = node.getResponseBuffer(0); // Nitrogen
    data[1] = node.getResponseBuffer(1); // Phosphorus
    data[2] = node.getResponseBuffer(2); // Potassium
  } else {
    data[0] = data[1] = data[2] = 0; // If communication fails, set NPK to 0
    Serial.println("Failed to read from NPK sensor");
  }

  // ** Debug Output to Serial Monitor **
  Serial.print("Soil Moisture (%): ");
  Serial.print(moisturePercentage);
  Serial.print(" | Condition: ");
  Serial.println(soilCondition);

  Serial.print("Nitrogen: ");
  Serial.print(data[0]);
  Serial.print(" | Phosphorus: ");
  Serial.print(data[1]);
  Serial.print(" | Potassium: ");
  Serial.println(data[2]);

  // ** Display Data on OLED **
  display.clearDisplay();

  // Line 1: Soil Moisture Percentage
  display.setCursor(0, 0);
  display.print("Moisture: ");
  display.print(moisturePercentage);
  display.print("% ");
  display.println(soilCondition);

  // Line 2: Nitrogen
  display.setCursor(0, 10);
  display.print("N:25% ");
  display.print(data[0]);

  // Line 3: Phosphorus
  display.setCursor(0, 20);
  display.print("P:0.2%");
  display.print(data[1]);

  // Line 4: Potassium
  display.setCursor(64, 20);
  display.print("K:0.1%");
  display.print(data[2]);

  // Update OLED
  display.display();

  delay(1000); // Wait for 1 second before the next reading
}

