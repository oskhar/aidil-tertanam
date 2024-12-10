#include <SPI.h>
#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup() {
  // Mulai komunikasi dengan Serial Monitor
  Serial.begin(9600);

  // Inisialisasi RTC
  if (! rtc.begin()) {
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

  // Tambahkan delay agar data tidak terlalu cepat muncul
  delay(1000);
}
