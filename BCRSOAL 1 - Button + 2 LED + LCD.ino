int pinLed1 = 13;
int pinLed2 = 14;
int pinButton = 26;
int pressCount = 0;
int buttonState = 0;
bool isActive = false;

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(pinLed1, OUTPUT);
  pinMode(pinLed2, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);
}
void loop() {
  buttonState = digitalRead(pinButton);
  if (buttonState == HIGH && isActive == false) {
    isActive = true;
    if (pressCount % 2 == 0){
      lcd.clear();
      digitalWrite(pinLed1, HIGH); 
      digitalWrite(pinLed2, LOW);
      lcd.print("Genap");
    } else if (pressCount % 5 == 0){
      lcd.clear();
      digitalWrite(pinLed1, LOW); 
      digitalWrite(pinLed2, HIGH);
      lcd.print("Oskhar Gans");
    } else if (pressCount % 2 != 0){
      lcd.clear();
      digitalWrite(pinLed1, LOW); 
      digitalWrite(pinLed2, LOW);
      lcd.print("Ganjil");
    }
    pressCount++;
  } else if (buttonState == LOW && isActive == true) {
    isActive = false; 
  }
  delay(50);
}