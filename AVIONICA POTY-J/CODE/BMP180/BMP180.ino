#include <Wire.h>
#include <EEPROM.h>

#define ADDRESS_SENSOR 0x77                 // Addresse du capteur
int eeAddress = 0; //EEPROM address to start reading from
int addr = 0; //EEPROM address to start reading from



unsigned long start = 0;
unsigned long last = 0;
int16_t  ac1, ac2, ac3, b1, b2, mb, mc, md; // Store sensor PROM values from BMP180
uint16_t ac4, ac5, ac6;                     // Store sensor PROM values from BMP180
// Ultra Low Power       OSS = 0, OSD =  5ms
// Standard              OSS = 1, OSD =  8ms
// High                  OSS = 2, OSD = 14ms
// Ultra High Resolution OSS = 3, OSD = 26ms
const uint8_t oss = 3;                      // Set oversampling setting
const uint8_t osd = 26;                     // with corresponding oversampling delay


float T, P, aux;                                 // Variables globales pour la température et la pression
// https://www.embarcados.com.br/arduino-acelerometro-giroscopio/
//Endereco I2C do MPU6050

#define pin 2
uint16_t W = 0;
//configurações iniciais
void setup()
{
  Serial.begin(9600);
  while (!Serial) {
  pinMode(pin,OUTPUT);
  
  delay(5000);
  Wire.begin();                             // Active le bus I2C
  init_SENSOR();                          // Initialise les variables
  delay(100);
  Wire.write(0x6B);
  //Inicializa o MPU-6050
  Wire.write(0);
  Wire.endTransmission(true);
}

void loop()
{
  int32_t b5;

  start = millis();



  b5 = temperature();                       // Lit et calcule la température (T)
  P = pressure(b5);                         // Lit et calcule la pressure (P)




if(P < aux)
{

digitalWrite(pin,HIGH);

}

aux = P;










/*

  if (start - last >= 100)// PASSIVO DE AJUSTE, NESSE CASO O PREEXIMENTO DA MEMÓRIA OCORRERÁ EM 25s.
  {
  
    EEPROM.write(eeAddress, (int)P);
    eeAddress ++;
    Serial.print(eeAddress);
    Serial.print("\t");
    Serial.print(sizeof((int)P));
    Serial.print(" ");
    Serial.print(start);
    Serial.print(" ");
    Serial.print("Pression: ");
    Serial.print((int)P);
    Serial.println(" mbar, ");

  }

  while (eeAddress >= 512)
  {  

    if(addr >= 512)
    {
      addr = 0;
    }
    else
    {
    Serial.print(addr);
    Serial.print(" "); 
    
    W = EEPROM.read(addr); 
   
    Serial.print(" "); 
    Serial.print(sizeof(W));
    Serial.print(" W:");
    Serial.print(W);
    Serial.print("\t");
    Serial.println("MEMORIA CHEIA");
    delay(10);
   
  }
   addr++;
  }

*/

}

/**********************************************
  Initialise les variables du capteur
 **********************************************/
void init_SENSOR()
{
  ac1 = read_2_bytes(0xAA);
  ac2 = read_2_bytes(0xAC);
  ac3 = read_2_bytes(0xAE);
  ac4 = read_2_bytes(0xB0);
  ac5 = read_2_bytes(0xB2);
  ac6 = read_2_bytes(0xB4);
  b1  = read_2_bytes(0xB6);
  b2  = read_2_bytes(0xB8);
  mb  = read_2_bytes(0xBA);
  mc  = read_2_bytes(0xBC);
  md  = read_2_bytes(0xBE);

  Serial.println("");
  Serial.println("Données de calibration du capteur :");
  Serial.print(F("AC1 = ")); Serial.println(ac1);
  Serial.print(F("AC2 = ")); Serial.println(ac2);
  Serial.print(F("AC3 = ")); Serial.println(ac3);
  Serial.print(F("AC4 = ")); Serial.println(ac4);
  Serial.print(F("AC5 = ")); Serial.println(ac5);
  Serial.print(F("AC6 = ")); Serial.println(ac6);
  Serial.print(F("B1 = "));  Serial.println(b1);
  Serial.print(F("B2 = "));  Serial.println(b2);
  Serial.print(F("MB = "));  Serial.println(mb);
  Serial.print(F("MC = "));  Serial.println(mc);
  Serial.print(F("MD = "));  Serial.println(md);
  Serial.println("");
}

/**********************************************
  Calcul de la pressure
 **********************************************/
float pressure(int32_t b5)
{
  int32_t x1, x2, x3, b3, b6, p, UP;
  uint32_t b4, b7;

  UP = read_pressure();                         // Lecture de la pression renvoyée par le capteur

  b6 = b5 - 4000;
  x1 = (b2 * (b6 * b6 >> 12)) >> 11;
  x2 = ac2 * b6 >> 11;
  x3 = x1 + x2;
  b3 = (((ac1 * 4 + x3) << oss) + 2) >> 2;
  x1 = ac3 * b6 >> 13;
  x2 = (b1 * (b6 * b6 >> 12)) >> 16;
  x3 = ((x1 + x2) + 2) >> 2;
  b4 = (ac4 * (uint32_t)(x3 + 32768)) >> 15;
  b7 = ((uint32_t)UP - b3) * (50000 >> oss);
  if (b7 < 0x80000000) {
    p = (b7 << 1) / b4;  // ou p = b7 < 0x80000000 ? (b7 * 2) / b4 : (b7 / b4) * 2;
  } else {
    p = (b7 / b4) << 1;
  }
  x1 = (p >> 8) * (p >> 8);
  x1 = (x1 * 3038) >> 16;
  x2 = (-7357 * p) >> 16;
  return (p + ((x1 + x2 + 3791) >> 4)) / 100.0f; // Retourne la pression en mbar
}

/**********************************************
  Lecture de la température (non compensée)
 **********************************************/
int32_t temperature()
{
  int32_t x1, x2, b5, UT;

  Wire.beginTransmission(ADDRESS_SENSOR); // Début de transmission avec l'Arduino
  Wire.write(0xf4);                       // Envoi l'adresse de registre
  Wire.write(0x2e);                       // Ecrit la donnée
  Wire.endTransmission();                 // Fin de transmission
  delay(5);

  UT = read_2_bytes(0xf6);                // Lecture de la valeur de la TEMPERATURE

  // Calcule la vrai température
  x1 = (UT - (int32_t)ac6) * (int32_t)ac5 >> 15;
  x2 = ((int32_t)mc << 11) / (x1 + (int32_t)md);
  b5 = x1 + x2;
  T  = (b5 + 8) >> 4;
  T = T / 10.0;                           // Retourne la température in celsius
  return b5;
}

/**********************************************
  Lecture de la pression
 **********************************************/
int32_t read_pressure()
{
  int32_t value;
  Wire.beginTransmission(ADDRESS_SENSOR);   // Début de transmission avec l'Arduino
  Wire.write(0xf4);                         // Envoi l'adresse de registre
  Wire.write(0x34 + (oss << 6));            // Ecrit la donnée
  Wire.endTransmission();                   // Fin de transmission
  delay(osd);
  Wire.beginTransmission(ADDRESS_SENSOR);
  Wire.write(0xf6);
  Wire.endTransmission();
  Wire.requestFrom(ADDRESS_SENSOR, 3);
  if (Wire.available() >= 3)
  {
    value = (((int32_t)Wire.read() << 16) | ((int32_t)Wire.read() << 8) | ((int32_t)Wire.read())) >> (8 - oss);
  }
  return value;                             // Renvoie la valeur
}

/**********************************************
  Lecture d'un byte sur la capteur BMP
 **********************************************/
uint8_t read_1_byte(uint8_t code)
{
  uint8_t value;
  Wire.beginTransmission(ADDRESS_SENSOR);
  Wire.write(code);
  Wire.endTransmission();
  Wire.requestFrom(ADDRESS_SENSOR, 1);
  if (Wire.available() >= 1)
  {
    value = Wire.read();
  }
  return value;
}

/**********************************************
  Lecture de 2 bytes sur la capteur BMP
 **********************************************/
uint16_t read_2_bytes(uint8_t code)
{
  uint16_t value;
  Wire.beginTransmission(ADDRESS_SENSOR);
  Wire.write(code);
  Wire.endTransmission();
  Wire.requestFrom(ADDRESS_SENSOR, 2);
  if (Wire.available() >= 2)
  {
    value = (Wire.read() << 8) | Wire.read();     // Récupère 2 bytes de données
  }
  return value;                                   // Renvoie la valeur
}

