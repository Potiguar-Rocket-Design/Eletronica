//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display
float voltagem = 0.0;
int tensaoC = 0;
int rt = 0;

void setup()
{
  Serial.begin(115200);
  lcd.init();                      // initialize the lcd
  lcd.backlight();
  lcd.clear();
}


void loop()
{

  tensaoC = analogRead(A0);

  rt =  map(tensaoC, 0, 830, 0, 100);
  
  lcd.setCursor(1, 0);
  lcd.print("PAINEL DE DISPARO");
  
  lcd.setCursor(0, 1);
  
  lcd.print("CAPACITORES: ");
  lcd.setCursor(14, 1);
  lcd.print(rt);
  lcd.setCursor(19, 1);
  lcd.print("%");

  Serial.println(rt);
  delay(50);
}
