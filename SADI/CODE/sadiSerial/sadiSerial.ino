#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

LiquidCrystal_I2C lcd(0x3F, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display


unsigned tensaoC = 0;
unsigned rt = 0;
unsigned long go = 0;
unsigned long last, last2 = 0;



// --- Mapeamento de Hardware ---
#define  ADDO 19// 14 Data Out 19
#define  ADSK 22// 16 SCK 22


// --- Protótipo das Funções Auxiliares ---
unsigned long ReadCount(); //conversão AD do HX711
unsigned long int milli_time;    //variable to hold the time

// --- Variáveis Globais ---
unsigned long convert;
                     //(14, 16); // (RX, TX)

void setup()
{
  Serial.begin(115200);
  
  
  Serial.println("Adafruit MLX90614 test");
  pinMode(ADDO, INPUT_PULLUP);   //entrada para receber os dados
  pinMode(ADSK, OUTPUT);         //saída para SCK
  
  mlx.begin();
  lcd.init();// initialize the lcd
  lcd.backlight();

  lcd.setCursor(4, 0);
  lcd.print("EQUIPE PRD");
  lcd.setCursor(1, 0);
  lcd.print("PAINEL DE DISPARO");
  delay(5000);
  
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("PESO: ");

  lcd.setCursor(0, 1);
  lcd.print("POTENCIA: ");

  lcd.setCursor(13, 1);
  lcd.print("%");

  lcd.setCursor(0, 2);
  lcd.print("STATUS: ");

  lcd.setCursor(0, 3);
  lcd.print("TEMPERATURA: ");

  lcd.setCursor(18, 3);
  lcd.print("C");

}


void loop()
{
  go = millis();

  tensaoC = analogRead(A0);






  if (go - last2 >= 1000)
  {
    convert = ReadCount();
    lcd.setCursor(13, 3);
    lcd.print(mlx.readObjectTempC());

    lcd.setCursor(6, 0);
    lcd.print(((-0.0002264 * convert) + 1877.7218), 2);


    lcd.setCursor(10, 0);
    lcd.print("kg");
    rt =  map(tensaoC, 0, 840, 0, 100);// 840 é o valor aproximado para correcao da tensao

    lcd.setCursor(10, 1);
    lcd.print(rt);



    last2 = go;
  }

  if ( rt >= 90) {
    lcd.setCursor(8, 2);
    lcd.print("CARREGADO!");

  }
  else if (rt > 10 && rt < 90)
  {
    lcd.setCursor(8, 2);
    lcd.print("CARREGANDO");

  }
  else
  {
    lcd.setCursor(8, 2);
    lcd.print("OFF");

  }


  Serial.println(rt);

}

// --- Funções ---
unsigned long ReadCount()
{
  unsigned long Count = 0;
  unsigned char i;

  digitalWrite(ADSK, LOW);

  while (digitalRead(ADDO));

  for (i = 0; i < 24; i++)
  {
    digitalWrite(ADSK, HIGH);
    Count = Count << 1;
    digitalWrite(ADSK, LOW);
    if (digitalRead(ADDO)) Count++;

  } //end for

  digitalWrite(ADSK, HIGH);
  Count = Count ^ 0x800000;
  digitalWrite(ADSK, LOW);

  return (Count);


} //end ReadCount
