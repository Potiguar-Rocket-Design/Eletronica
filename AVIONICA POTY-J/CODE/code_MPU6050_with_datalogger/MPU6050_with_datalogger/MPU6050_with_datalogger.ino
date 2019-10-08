#include "Arduino.h"
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <SPI.h>
#include <SD.h>



MPU6050 accelgyro;
Adafruit_BMP085 bmp;


unsigned long start, t0,tf,delta;

unsigned long guardar = 0;
unsigned long cont = 0;
const int chipSelect = 10;
float alt, alt2, soma;
int16_t ax, ay, az;
int16_t gx, gy, gz;


void setup() {
  Wire.begin();
  Serial.begin(38400);
  accelgyro.initialize();

  if (!bmp.begin())
  {
    Serial.println("Could not find a valid BMP085 sensor, check wiring!");
    while (1) {}
  }

  Serial.print("Initializing SD card...");

  if (!SD.begin(chipSelect))
  {
    Serial.println("Card failed, or not present");
    return;
  }
  Serial.println("card initialized.");
  Serial.println("Initializing I2C devices...");

  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  
  for(int i = 0; i < 5; i++)
  {
    soma = soma + bmp.readAltitude(100700);
    
  }
    alt = soma/5;
Serial.print("ALTITUDE INICIAL: ");
Serial.println(alt);
}

void loop()
{
  start = millis();
  cont = micros();
  t0 = cont;// 
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  
  alt2 = (bmp.readAltitude(100700)) - alt;
  
  Serial.print(start);
  Serial.print(" ");
  Serial.println(guardar);


  if ((start - guardar) >= 10000.0)
  {
    File dataFile = SD.open("datalog.txt", FILE_WRITE);
   
     
    if (dataFile)
    {
     
      dataFile.print(guardar);//16 bits
      dataFile.print(",");//8 bits
      dataFile.print(ax);//16 bits
      dataFile.print(",");//8 bits
      dataFile.print(ay);//16 bits
      dataFile.print(",");//8 bits
      dataFile.print(az);//16 bits
      dataFile.print(",");//8 bits
      dataFile.print(gx);//16 bits
      dataFile.print(",");//8 bits
      dataFile.print(gy);//16 bits
      dataFile.print(",");//8 bits
      dataFile.print(gz);//16 bits
      dataFile.print(",");//8 bits
      dataFile.println(alt2);//16 bits
      dataFile.close();//136 bits ------ fechar o arq depois de um tempo, intervalo de leitura de 10s pra fechar o arquivo
      Serial.println("OK");
    }
   else
   {
     Serial.println("error opening datalog.txt");
   }
    guardar = start;// serve para reiniciar o cronometro
  }
  //
   tf = cont;
  Serial.print("ALTITUDE: ");
  Serial.println(alt2);
  Serial.print("T0: ");
  Serial.println(t0);// tempo que leva pra fazer uma gravação
  Serial.print("Tf: ");
  Serial.println(tf);// tempo que leva pra fazer uma gravação
 
}
