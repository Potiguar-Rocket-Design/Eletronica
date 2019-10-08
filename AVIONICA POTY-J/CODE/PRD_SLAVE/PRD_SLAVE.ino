
#include <Wire.h>                //Inclui a biblioteca I2C
#include <SPI.h>
#include <LoRa.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>

#define GPS_RX 3
#define GPS_TX 4
#define GPS_Serial_Baud 9600
 
TinyGPS gps;
 
SoftwareSerial gpsSerial(GPS_RX, GPS_TX);
 

void setup()
{
 Serial.begin(GPS_Serial_Baud);
  gpsSerial.begin(GPS_Serial_Baud);
  Wire.begin(15);                //Barramento I2C do endereço 15
  Wire.onReceive(receiveEvent);  //Recepção de dados (chama função auxiliar)
  Serial.begin(9600);            //Inicia comunicação Serial com 9600 de baud rate
  while (!Serial);

  //Serial.println("LoRa Sender");

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    //while (1);
  }

}

void loop()
{
bool newData = false;
  unsigned long chars;
  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (gpsSerial.available())
    {
      char c = gpsSerial.read();
      // Serial.write(c); //apague o comentario para mostrar os dados crus
      if (gps.encode(c)) // Atribui true para newData caso novos dados sejam recebidos
        newData = true;
    }
  }
  if (newData)
  {
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);

   Serial.print("Sending packet: ");
   LoRa.beginPacket();

    
    LoRa.print("LAT=");
    LoRa.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    LoRa.print(" LON=");
    LoRa.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    LoRa.print(" SAT=");
    LoRa.print(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
    LoRa.print(" PREC=");
    LoRa.print(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop());
    LoRa.println();
    LoRa.endPacket();



    Serial.print("LAT=");
    Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    Serial.print(" LON=");
    Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    Serial.print(" SAT=");
    Serial.print(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
    Serial.print(" PREC=");
    Serial.print(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop());
    Serial.println();
    Serial.println();

  }  
}

//Função auxiliar para processar os dados recebidos do Master
void receiveEvent(int howMany)
{
  while (1 < Wire.available()) //Loop para receber toda String de dados
  {
    char c = Wire.read();      //Recebe um byte caractere
    Serial.print(c);           //Imprime na Serial
  }
  // Serial.println("\n");           //Imprime na Serial
}
