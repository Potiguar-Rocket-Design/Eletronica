#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <SoftwareSerial.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

LiquidCrystal_I2C lcd(0x3F, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display
SoftwareSerial sadi(14, 16); // (RX, TX)

// --- Mapeamento de Hardware ---
#define  ADDO 19 // 14 Data Out 19
#define  ADSK 22 // 16 SCK 22



int dados[5];
int chegou = 0;
int counter = 0;

// --- Protótipo das Funções Auxiliares ---
unsigned long ReadCount(); //conversão AD do HX711
unsigned long int milli_time;    //variable to hold the time

// --- Variáveis Globais ---
unsigned long convert;
unsigned tensaoC, rt = 0;

unsigned long go, last = 0;



void setup()
{
  Serial.begin(115200);
  sadi.begin(9600);

  pinMode(ADDO, INPUT_PULLUP);   //entrada para receber os dados
  pinMode(ADSK, OUTPUT);         //saída para SCK



  Serial.println("Comunicação Serial Pronto!");
  mlx.begin();

  Serial.println("Sensor de Temperatura MLX90614 Pronto!");

  lcd.init();// initialize the lcd
  lcd.clear();
  Serial.println("LCD Pronto!");
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


  if (sadi.available())
  {

    chegou = sadi.read();

    for (int i = 0; i < 5; i++)
    {
      dados[i] = chegou & (0x01 << i);

      if (dados[i]) counter += 1; // conta a quantidade de 1 para a paridade
    }

  }

  bool paridade = dados[4];

  if ( counter % 2 == paridade) {

    sadi.write(10001);

  }
  else {
    sadi.write(01110);
  }





  if (go - last >= 1000)
  {
    show();

    last = go;
  }



}
