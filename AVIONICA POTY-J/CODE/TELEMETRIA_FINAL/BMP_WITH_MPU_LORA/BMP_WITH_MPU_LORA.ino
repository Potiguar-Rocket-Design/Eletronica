#include <Wire.h>
#include <SPI.h>
#include <LoRa.h>

#define ADDRESS_SENSOR 0x77                 // Addresse du capteur
//Endereco I2C do MPU6050
const int MPU_addr = 0x68; //Endereço do sensor

int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ; //Variaveis para pegar os valores medidos

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

int voltagem = 0;
float T, P;                                 // Variables globales pour la température et la pression
// https://www.embarcados.com.br/arduino-acelerometro-giroscopio/


#define pin 3
#define bat A3

uint16_t W = 0;
//configurações iniciais
void setup()
{
  Serial.begin(9600);
  /*
  while (!Serial)
  {

  }
  */
  pinMode(pin, OUTPUT);
  pinMode(bat, INPUT);

  delay(5000);
  Wire.begin();                             // Active le bus I2C
  init_SENSOR();                          // Initialise les variables
  delay(100);
  Wire.write(0x6B);
  //Inicializa o MPU-6050
  Wire.write(0);
  Wire.endTransmission(true);

  Wire.beginTransmission(MPU_addr); //Começa a transmissao de dados para o sensor
  Wire.write(0x6B); // registrador PWR_MGMT_1
  Wire.write(0); // Manda 0 e "acorda" o MPU 6050
  Wire.endTransmission(true);

 // signalBandwidth - signal bandwidth in Hz, defaults to 125E3
 // LoRa.setSignalBandwidth(signalBandwidth); // 7.8E3, 10.4E3, 15.6E3, 20.8E3, 31.25E3, 41.7E3, 62.5E3, 125E3, and 250E3.
 
  if (!LoRa.begin(915E6))
  {
    Serial.println(" LoRa Falhou!");
    digitalWrite(pin,HIGH);
    while (1);
  }
   
  Serial.println("LoRa Pronto!!");

}

void loop()
{
  start = millis();
  
  int32_t b5;  
  b5 = temperature();                       // Lit et calcule la température (T)
  P = pressure(b5);                         // Lit et calcule la pressure (P)

  voltagem = digitalRead(A3); // leitura da bateria



  Wire.beginTransmission(MPU_addr); //Começa a transmissao de dados para o sensor
  Wire.write(0x3B); // registrador dos dados medidos (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true); // faz um "pedido" para ler 14 registradores, que serão os registrados com os dados medidos
  AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)



  if (start - last >= 1000)// PASSIVO DE AJUSTE, NESSE CASO O PREEXIMENTO DA MEMÓRIA OCORRERÁ EM 25s.
  {
    LoRa.beginPacket();
    
    LoRa.print(P);
   
    LoRa.print(AcY);
  
    LoRa.print(AcZ);
  
    LoRa.print(Tmp / 340.00 + 36.53); //Equação da temperatura em Cº de acordo com o datasheet
  
    LoRa.print(GyX);
   
    LoRa.print(GyY);
   
    LoRa.print(GyZ);
    
    LoRa.println(voltagem);
    
    LoRa.endPacket();


// FUNCAO DE TRANSFORMAÇÃO:   alt = (44330.0*(1-pow(P/P0,1/5.255))); 
//                                     P0  --> ALTURA INICIAL BASELINE
//                                     P   --> ALTURA ATUAL
    Serial.print(P);
    Serial.print("\t");
    Serial.print(AcY);
    Serial.print("\t");
    Serial.print(AcZ);
    Serial.print("\t");
    Serial.print(Tmp / 340.00 + 36.53); //Equação da temperatura em Cº de acordo com o datasheet
    Serial.print("\t");
    Serial.print(GyX);
    Serial.print("\t");
    Serial.print(GyY);
    Serial.print("\t");
    Serial.print(GyZ);
    Serial.print("\t");
    Serial.println(voltagem);
    
    digitalWrite(pin, !digitalRead(pin));
    last = start;

  }




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

