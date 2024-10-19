#include <DHT.h>;
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
#define DHTPIN 13
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup () {
  Serial.begin(115200);
  Serial.println(F("DHT22 test!"));
  dht.begin();
  lcd.init();
  lcd.backlight();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  lcd.setCursor(0, 0);
  lcd.print("Humidity: ");
  lcd.setCursor(10, 0);
  lcd.print(h);
  lcd.setCursor(0, 1);
  lcd.print("Temperature: ");
  lcd.setCursor(13, 1);
  lcd.print(t);

  delay(2000);
  lcd.clear();
}
