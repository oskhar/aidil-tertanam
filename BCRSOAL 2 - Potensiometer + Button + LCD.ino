int Potensiometer = 14;
int pinButton = 13;
int buttonState = 0;
int isActive = false;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void loop() {
  int PotensiometerV = analogRead(Potensiometer);
  buttonState = digitalRead(pinButton);
  if (buttonState == HIGH && isActive == false) {
    isActive = true;
    lcd.clear();
    lcd.print(PotensiometerV);
    lcd.setCursor(0, 1);
    lcd.print(potValue);
  } else if (buttonState == LOW && isActive == true) {
    isActive = false; 
  }
  delay(100);
}
