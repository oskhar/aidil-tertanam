// Pin LDR
const int LDR1_PIN = 35; // Pin ADC1 untuk LDR1
const int LDR2_PIN = 32; // Pin ADC2 untuk LDR2

  #include <ESP32Servo.h>

  int servoPin = 19;
  int deg = 90;

  Servo servo1;

void setup() {
  Serial.begin(9600);
  // Konfigurasi pin sebagai input (tidak wajib karena ADC defaultnya input)
  pinMode(LDR1_PIN, INPUT);
  pinMode(LDR2_PIN, INPUT);
  servo1.attach(servoPin);
    servo1.write(0);
}

void loop() {
  // Membaca nilai ADC dari LDR
  int ldr1Value = analogRead(LDR1_PIN); // Membaca LDR1
  int ldr2Value = analogRead(LDR2_PIN); // Membaca LDR2

  // Konversi nilai ke persentase (opsional)
  float ldr1Percent = (ldr1Value / 4095.0) * 100; // ESP32 ADC memiliki resolusi 12-bit
  float ldr2Percent = (ldr2Value / 4095.0) * 100;

  // Tampilkan hasil ke Serial Monitor
  Serial.print("LDR1: ");
  Serial.print(ldr1Value);
  Serial.print(" (");
  Serial.print(ldr1Percent);
  Serial.print("%)");
  Serial.print(" | LDR2: ");
  Serial.print(ldr2Value);
  Serial.print(" (");
  Serial.print(ldr2Percent);
  Serial.println("%)");

  if(ldr1Value == ldr2Value){
    servo1.write(deg);
  }else if(ldr1Value > ldr2Value){
    if(deg < 180){

      deg += 1;
    }
    servo1.write(deg);
  }else if(ldr1Value < ldr2Value){
    if(deg > 0){

      deg -= 1;
    }
    servo1.write(deg);
  }
  Serial.println(deg);

  delay(500);
}
