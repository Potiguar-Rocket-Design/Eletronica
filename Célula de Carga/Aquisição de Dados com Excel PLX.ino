
// --- Mapeamento de Hardware ---
#define  ADDO  9    //Data Out 19
#define  ADSK  10   //SCK 22


// --- Protótipo das Funções Auxiliares ---
unsigned long ReadCount(); //conversão AD do HX711
unsigned long int milli_time;    //variable to hold the time

// --- Variáveis Globais ---
unsigned long convert;



// --- Configurações Iniciais ---
void setup()
{
  pinMode(ADDO, INPUT_PULLUP);   //entrada para receber os dados
  pinMode(ADSK, OUTPUT);         //saída para SCK
  Serial.begin(9600);               //Fastest baudrate
  Serial.println("CLEARDATA");        //This string is defined as a 
                                      // commmand for the Excel VBA 
                                      // to clear all the rows and columns
 Serial.println("LABEL,Computer Time,Time (Milli Sec.),Data");  
                                      //LABEL command creates label for 
                                      // columns in the first row with bold font

} //end setup


// --- Loop Infinito ---
void loop()
{


  convert = ReadCount();
 
 milli_time = millis();
  
Serial.print("DATA,TIME,");  
Serial.print(milli_time);
Serial.print(",");
// Serial.println(random(10,20));
 Serial.print(convert);
 Serial.print(",");
 Serial.println((-0.0002264*convert)+1877.7218);




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









