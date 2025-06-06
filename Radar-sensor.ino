#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD Setup (Address: 0x27 or 0x3F)
LiquidCrystal_I2C lcd(0x3F, 16, 2);

// Servo Setup
Servo radarServo;
const int servoPin = 9;

// Ultrasonic Sensor Pins
const int trigPin = 10;
const int echoPin = 11;

// Radar Scanning Settings
const int minAngle = 15;   // Start angle (avoid 0° for servo safety)
const int maxAngle = 165;  // End angle
const int stepAngle = 5;   // Degree increment per step

void setup() {
  Serial.begin(9600);  // For debugging
  
  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Radar System");
  lcd.setCursor(0, 1);
  lcd.print("Scanning...");
  
  // Attach Servo
  radarServo.attach(servoPin);
  
  // Ultrasonic Pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  delay(2000);
  lcd.clear();
}

void loop() {
  // Forward Sweep (15° → 165°)
  for (int angle = minAngle; angle <= maxAngle; angle += stepAngle) {
    updateRadar(angle);
  }
  
  // Reverse Sweep (165° → 15°)
  for (int angle = maxAngle; angle >= minAngle; angle -= stepAngle) {
    updateRadar(angle);
  }
}

void updateRadar(int angle) {
  radarServo.write(angle);  // Move servo
  delay(50);                // Stabilize
  
  float distance = getDistance();  // Measure distance
  
  // Display on LCD
  lcd.setCursor(0, 0);
  lcd.print("Angle: ");
  lcd.print(angle);
  lcd.print("° ");
  
  lcd.setCursor(0, 1);
  lcd.print("Dist: ");
  if (distance == 0) {
    lcd.print("---");
  } else {
    lcd.print(distance);
    lcd.print("cm");
  }
  
  // Serial Output (for plotting)
  Serial.print(angle);
  Serial.print(",");
  Serial.println(distance);
}

float getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.0343 / 2;  // Convert to cm
  
  // Filter out invalid readings
  if (distance > 400 || distance < 2) distance = 0;
  
  return distance;
}