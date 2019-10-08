#include <SoftwareSerial.h>

SoftwareSerial esp32(14, 12, false, 256);// RX, TX


unsigned i = 0;

void setup() {

  Serial.begin(115200);
  Serial.println("\nComunicação Serial Iniciada");
  esp32.begin(9600);





}

void loop() {

  i++;
  esp32.println(i);
  Serial.println(i);
  delay(500);

}
