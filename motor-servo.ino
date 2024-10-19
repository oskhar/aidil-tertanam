#include <ESP32Servo.h>

int servoPin = 12;

Servo servo1;

void setup() {
  Serial.begin(9600);
  servo1.attach(servoPin);
  servo1.write(0);
}

void loop() {
  for(int i = 0; i <= 180; i++) {
    servo1.write(i);
    Serial.print("Putaran ke: ");
    Serial.println(i);
    delay(1);
  }

  for(int i = 180; i >= 0; i--) {
    servo1.write(i);
    Serial.print("Putaran ke: ");
    Serial.println(i);
    delay(1);
  }
}
