#include <SPI.h>
#include <LoRa.h>

void setup() {
  Serial.begin(9600);
  Serial.println("CLEARDATA");
  Serial.println("LABEL,Computer Time, SIGNAL, RSSI, SNR");

 // while (!Serial);
 
  if (!LoRa.begin(915E6))
  {
    Serial.println("LoRa Falha!");
    while (1);
  }
   Serial.println("LoRa Pronto");
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  float snr = LoRa.packetSnr();

  if (packetSize) {

    Serial.print("DATA,TIME,");
    // read packet
    while (LoRa.available())
    {

      // TALVEZ DÁ QUEBRA DE LINHA AJUDA
      Serial.print((char)LoRa.read());
    }
    Serial.print(",");
    //RSSI 
    Serial.print(LoRa.packetRssi());    
    Serial.print(",");
    //SNR 
    Serial.println(snr);
    
  }
}
