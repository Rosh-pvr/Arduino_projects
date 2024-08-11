#include <LiquidCrystal_I2C.h>
#include <DHT.h>


String tempMessage;
String humMessage;

void setup() {
  LiquidCrystal_I2C lcd(0x20,4,5,6,0,1,2,3,7,NEGATIVE);
  DHT dht(7,DHT11);
  lcd.begin((16,2);
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("DHT11 Sensor");
  dht.begin();
  Serial.begin(9600);
  Serial.println("Temperature and Humidity);
 

}

void loop() {
 float h =dht.readHumidity();
 float t = dht.readTemperature();
 if(isnan(h)||isnan(t))
 {
  Serial.println("Failed to read from DHT sensor");
  loop();
 }
 tempMessage = "Temp: " + String(t)+ "C";
 humMessage = "Hum:" + String(h) + "%";
 Serial.print(tempMessage + "  ");
 Serial.print(humMessage);
 lcd.clear();
 lcd.setCursor(1,0);
 lcd.print(tempMessage);
 lcd.setCursor(1,1);
 lcd.print(humMessage);
 delay(1000);
 

}
