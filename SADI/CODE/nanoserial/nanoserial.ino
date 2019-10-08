#include <SoftwareSerial.h>

SoftwareSerial nano(2, 3); // RX, TX


unsigned i = 10000;
unsigned start, last = 0;

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(115200);



  Serial.println("Comunicação Serial Iniciada");

  // set the data rate for the SoftwareSerial port
  nano.begin(9600);

}

void loop() // run over and over
{

  start = millis();
/*
 if(start - last >= 500){

  i--;
  nano.println(i);
  Serial.println(i);
  last = start;
 }
 */
  if (nano.available() > 0) {
  Serial.write(nano.read());
  }

}
