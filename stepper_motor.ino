#include <Stepper.h>

// Define the number of steps per revolution for your motor
const int stepsPerRevolution = 2048;

// Initialize the stepper library on pins 8 through 11
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  // Set the speed of the motor (in RPM)
  myStepper.setSpeed(15);
  // Begin Serial communication at a baud rate of 9600:
  Serial.begin(9600);
}

void loop() {
  // Step one revolution in one direction:
  Serial.println("clockwise");
  myStepper.step(stepsPerRevolution);
  delay(1000);

  // Step one revolution in the other direction:
  Serial.println("counterclockwise");
  myStepper.step(-stepsPerRevolution);
  delay(1000);
}
