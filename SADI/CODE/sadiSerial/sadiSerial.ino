#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <SoftwareSerial.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

LiquidCrystal_I2C lcd(0x3F, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display


unsigned tensaoC, rt = 0;

unsigned long go, last = 0;



// --- Mapeamento de Hardware ---
#define  ADDO 19 // 14 Data Out 19
#define  ADSK 22 // 16 SCK 22

char message[16];


// --- Protótipo das Funções Auxiliares ---
unsigned long ReadCount(); //conversão AD do HX711
unsigned long int milli_time;    //variable to hold the time

// --- Variáveis Globais ---
unsigned long convert;

SoftwareSerial sadi(14, 16); // (RX, TX)

void setup()
{
  Serial.begin(115200);
  
  sadi.begin(9600);
  Serial.println("Comunicação Serial Pronto!");
  mlx.begin();
  
  Serial.println("Sensor de Temperatura MLX90614 Pronto!");

  lcd.init();// initialize the lcd
  Serial.println("LCD Pronto!");
  lcd.backlight();

  pinMode(ADDO, INPUT_PULLUP);   //entrada para receber os dados
  pinMode(ADSK, OUTPUT);         //saída para SCK



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


if (sadi.available() > 0) {


// estudar bit de paridade para comSerial
  for(int i = 0; i < 5; i++){
    char dados = sadi.read();
  }
  Serial.write();
  }





  if (go - last >= 1000)
  {
    

    show();


    last = go;
  }



}
