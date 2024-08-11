int ir = 7;
int buzzer=8;
int x;

void setup() {
  Serial.begin(9600);
  pinMode(8,INPUT);
  pinMode(7,OUTPUT);
  // put your setup code here, to run once:

}

void loop() {
  x = digitalRead(ir);
  // put your main code here, to run repeatedly:
Serial.println(x);
delay(100);
if(x==1)
{
  digitalWrite(8,LOW);
}
else{
  digitalWrite(8,HIGH);
  
}
}
