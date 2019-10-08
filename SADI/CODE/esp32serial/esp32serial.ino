#include <SoftwareSerial.h>

SoftwareSerial esp32(14, 12);// RX, TX'


unsigned i = 0;
unsigned start, last = 0;

void setup() {

  Serial.begin(115200);
  Serial.println("\nComunicação Serial Iniciada");
  esp32.begin(9600);


}

void loop() {

 start = millis();

 if(start - last >= 500){

  i++;
  esp32.println(i);
  Serial.println(i);
  last = start;
 }
/*
if (esp32.available() > 0) {
  Serial.write(esp32.read());
  }
  */
}
