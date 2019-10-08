
// ------- Funções ---
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
