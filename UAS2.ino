#include <SPI.h>
#include <Wire.h>
#include "RTClib.h"
#include <ESP32Servo.h>

RTC_DS3231 rtc;

// Pin LDR
const int LDR1_PIN = 35; // Pin ADC1 untuk LDR1
const int LDR2_PIN = 32; // Pin ADC2 untuk LDR2

int servoPin = 19;
int deg = 90;

Servo servo1;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup() {
  // Mulai komunikasi dengan Serial Monitor
  Serial.begin(9600);

  // Konfigurasi pin sebagai input (tidak wajib karena ADC defaultnya input)
  pinMode(LDR1_PIN, INPUT);
  pinMode(LDR2_PIN, INPUT);

  servo1.attach(servoPin);
  servo1.write(0); // Mulai dengan posisi servo 0°

  // Inisialisasi RTC
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  // Atur waktu RTC sesuai dengan waktu kompilasi sketch
  rtc.adjust(DateTime(__DATE__, __TIME__));
}

void loop() {
  DateTime now = rtc.now(); // Ambil waktu saat ini dari RTC

  // Tampilkan informasi waktu di Serial Monitor
  Serial.print("Time: ");
  Serial.print(now.hour(), DEC);  // Jam
  Serial.print(":");
  Serial.print(now.minute(), DEC); // Menit
  Serial.print(":");
  Serial.println(now.second(), DEC); // Detik

  Serial.print("Date: ");
  Serial.print(now.day(), DEC); // Hari
  Serial.print("-");
  Serial.print(now.month(), DEC); // Bulan
  Serial.print("-");
  Serial.println(now.year(), DEC); // Tahun

  Serial.print("Day of the week: ");
  Serial.println(daysOfTheWeek[now.dayOfTheWeek()]); // Nama hari

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

  // Cek waktu sekarang dan hitung sudut servo berdasarkan waktu
  int currentHour = now.hour();
  int currentMinute = now.minute();

  // Tentukan waktu awal (5:30 AM) dan waktu akhir (6:30 PM)
  int startHour = 5;   // Jam mulai (5:00 AM)
  int startMinute = 30; // Menit mulai (30 menit)

  int endHour = 18;    // Jam berakhir (6:00 PM)
  int endMinute = 30;   // Menit berakhir (30 menit)

  // Hitung waktu dalam menit dari jam 5:30 AM
  int startTimeInMinutes = startHour * 60 + startMinute;
  int endTimeInMinutes = endHour * 60 + endMinute;
  int currentTimeInMinutes = currentHour * 60 + currentMinute;

  // Cek apakah waktu sekarang ada dalam rentang waktu yang ditentukan
  if (currentTimeInMinutes >= startTimeInMinutes && currentTimeInMinutes <= endTimeInMinutes) {
    // Hitung persentase waktu yang telah berlalu
    int elapsedTime = currentTimeInMinutes - startTimeInMinutes;
    int totalTime = endTimeInMinutes - startTimeInMinutes;

    // Mapped deg: 0° pada 5:30 AM dan 180° pada 6:30 PM
    deg = map(elapsedTime, 0, totalTime, 0, 180);

    // Update posisi servo
    servo1.write(deg);
    Serial.print("Servo position: ");
    Serial.println(deg);
  }

  // delay(500);

  // Tambahkan delay agar data tidak terlalu cepat muncul
  delay(1000);
}
