void show() {

  lcd.setCursor(13, 3);
  lcd.print(mlx.readObjectTempC());

  convert = ReadCount();
  lcd.setCursor(6, 0);
  lcd.print(((-0.0002264 * convert) + 1877.7218), 2);


  lcd.setCursor(10, 0);
  lcd.print("kg");
  tensaoC = analogRead(A0);
  rt =  map(tensaoC, 0, 840, 0, 100);// 840 é o valor aproximado para correcao da tensao

  lcd.setCursor(10, 1);
  lcd.print(rt);

  Serial.println(rt);

  if ( rt >= 90) {
    lcd.clear();
    lcd.setCursor(8, 2);
    lcd.print("CARREGADO!");

  }
  else if (rt > 10 && rt < 90)
  {
    lcd.clear();
    lcd.setCursor(8, 2);
    lcd.print("CARREGANDO");

  }
  else
  {
    lcd.clear();
    lcd.setCursor(8, 2);
    lcd.print("OFF");

  }
}
