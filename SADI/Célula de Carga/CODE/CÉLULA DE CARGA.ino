#include <SPI.h>
#include <SD.h>


// --- Mapeamento de Hardware ---
#define  ADDO  8    //Data Out
#define  ADSK  9    //SCK


const int chipSelect = 10;// SD CARD
unsigned long start = 0;





// --- Protótipo das Funções Auxiliares ---
unsigned long ReadCount(); //conversão AD do HX711
unsigned long convert;// --- Variáveis Globais ---


// --- Configurações Iniciais ---
void setup()
{
  Serial.begin(9600);
  pinMode(ADDO, INPUT_PULLUP);   //entrada para receber os dados
  pinMode(ADSK, OUTPUT);         //saída para SCK

} //end setup


// --- Loop Infinito ---
void loop()
{

  start = millis();
  convert = ReadCount();

  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  if (dataFile)
  {
    dataFile.print(start);  
     dataFile.print("\t");
      dataFile.print(convert);    
    dataFile.close();
  }
  else
  {
    Serial.println("error opening datalog.txt");
  }


  Serial.print("VALORES: ");
  Serial.println(convert);

} //end loop


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









