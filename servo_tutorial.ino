#include <Servo.h>          //library for controlling a servo
const  byte potMeter=A0;     //potentiometer attached to analog port A3
int potMeterValue=0;
byte  rotation=0;
Servo myServo;              //name your servo

void setup()  {
  myServo.attach(9);        //servo attached to digital port 2
  pinMode(potMeter,INPUT);  //potentiometer is an input=>it sends information to the computer
  Serial.begin(9600);       //start serial communication at 9600 baud
}

void loop() {
  potMeterValue=analogRead(potMeter);
  rotation=map(potMeterValue,0,1023,0,180);      
  myServo.write(rotation);
  delay(100);              //you can delete the delay, but on the serial  monitor  there will be too much information
  Serial.print("Potmetervalue: ");
  Serial.print(potMeterValue);             
  Serial.print("\  ");
  Serial.print("rotation: ");
  Serial.println(rotation);
  Serial.println();
}
