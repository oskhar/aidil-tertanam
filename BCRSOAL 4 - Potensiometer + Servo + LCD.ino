#include <ESP32Servo.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int servoPin = 14;
int PotensiometerPin = 26;
int buttonPin = 13;
int buttonState = 0;
bool berlawanan = false;
int pressCount = 0;
bool isActive = false;
int lastSudut = 0;
int sudut = 0;

Servo servo1;

void setup() {
  Serial.begin(9600);
  servo1.attach(servoPin);
  servo1.write(0);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  int analogValue = analogRead(PotensiometerPin);
  buttonState = digitalRead(buttonPin);
  sudut = map(analogValue, 0, 4095, 0, 180);
  // if (berlawanan)
  //   sudut = map(analogValue, 0, 180, 0, 4095);

  if (berlawanan)
    sudut = lastSudut - sudut;

  servo1.write(sudut);

  if (buttonState == HIGH && isActive == false) {
    isActive = true;
    if (pressCount % 2 == 0){
      berlawanan = true;
      lastSudut = sudut;
    } else if (pressCount % 2 != 0){
      berlawanan = false;
      lastSudut = sudut;
    }
    pressCount++;
    Serial.println(pressCount);
  } else if (buttonState == LOW && isActive == true) {
    isActive = false; 
  }

  delay(100);
}
