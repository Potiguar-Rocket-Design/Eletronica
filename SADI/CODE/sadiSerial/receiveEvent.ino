// funcao executada sempre que algum dado e recebido no barramento I2C
// vide "void setup()"
void receiveEvent(int howMany) {
  if (Wire.available())
  {
    char valor = Wire.read();
    Serial.println("DADO RECEBIDO");
    if (valor == 0)
    {
      digitalWrite(carregar, LOW);

      Serial.println("DESLIGADO");
    }
    else if (valor == 1)
    {
      digitalWrite(carregar, HIGH);
      Serial.println("LIGADO");
    }
    else if (valor == 2)
    {
      digitalWrite(ignitar, HIGH);
      Serial.println("LIGADO");
    }
    else if (valor == 3)
    {
      digitalWrite(ignitar, LOW);
      Serial.println("LIGADO");
    }
    else
    {
      Serial.println("Desconhecido");
    }
  }
}
