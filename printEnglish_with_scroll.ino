#include<LiquidCrystal_I2C_Hangul.h>
#include<Wire.h>

LiquidCrystal_I2C_Hangul lcd(0x3F,16,2); //LCD 클래스 초기화

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.print("GRS ELECTRONICS HOBBY TUTORING CENTRE");
  lcd.setCursor(0,1); 
  lcd.print("         For IOT Classes");
  
  
}

void loop() {
 

   for(int PositionCount=0; PositionCount<29; PositionCount++)
   {
    lcd.setCursor(0,1);
    lcd.scrollDisplayRight(); //builtin command to scroll right the text
    delay(900);//delay of 150 msec
    }
   
}
