int LedPin = 2;


void setup() {
  pinMode(LedPin,OUTPUT);
     digitalWrite(LedPin,LOW);
  

}

void loop() {
  digitalWrite(LedPin,HIGH);
  delay(500);
  // put your main code here, to run repeatedly:
  digitalWrite(LedPin,LOW);
  delay(500);
}
