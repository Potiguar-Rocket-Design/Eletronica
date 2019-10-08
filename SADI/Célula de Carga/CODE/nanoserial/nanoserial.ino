/*
  Software serial multple serial test

  Receives from the hardware serial, sends to software serial.
  Receives from software serial, sends to hardware serial.

  The circuit:
   RX is digital pin 2 (connect to TX of other device)
   TX is digital pin 3 (connect to RX of other device)

  created back in the mists of time
  modified 9 Apr 2012
  by Tom Igoe
  based on Mikal Hart's example

  This example code is in the public domain.

*/
#include <SoftwareSerial.h>

SoftwareSerial nano(2, 3); // RX, TX

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
  if (nano.available() > 0) {
  Serial.write(nano.read());
  }

}
