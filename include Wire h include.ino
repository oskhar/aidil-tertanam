#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
int row = 0, col = 0;

void setup() {
  lcd.init();
  lcd.backlight();
  
}
void loop() {
  

  lcd.setCursor(row, col);
  lcd.print("Parit Jelek");
  row += 1;
  delay(1000);
  lcd.clear();

}
