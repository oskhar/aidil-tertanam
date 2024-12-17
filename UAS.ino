#include <SPI.h>
#include <Wire.h>
#include "RTClib.h"
#include <ESP32Servo.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

const char* ssid = "realme";
const char* password = "12345678";
const char* botToken = "7717841869:AAHsyUb9XCHuZjfBqgOqg7_MwmtltTcLSeY";
const char* chatID = "5464641183";

WiFiClientSecure client;
UniversalTelegramBot bot(botToken, client);

RTC_DS3231 rtc;

// Pin LDR
const int LDR1_PIN = 35; // Pin ADC1 untuk LDR1
const int LDR2_PIN = 32; // Pin ADC2 untuk LDR2
const int RELAY_PIN = 27;

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
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);

  servo1.attach(servoPin);
  servo1.write(0); // Mulai dengan posisi servo 0°

  // Inisialisasi RTC
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Mencoba menghubungkan ke WiFi...");
  }
  Serial.println("Terhubung ke WiFi!");

  client.setInsecure();
  bot.sendMessage(chatID, "Bot Telegram sudah terhubung dengan ESP32!", "");

  // Atur waktu RTC sesuai dengan waktu kompilasi sketch
  rtc.adjust(DateTime(__DATE__, __TIME__));
}

void loop() {
  DateTime now = rtc.now(); // Ambil waktu saat ini dari RTC
  bool isNight = now.hour() >= 18 || now.hour() < 6;
  int relayState = digitalRead(RELAY_PIN);

  if (isNight && relayState == HIGH) digitalWrite(RELAY_PIN, LOW);
  if (!isNight && relayState == LOW) digitalWrite(RELAY_PIN, HIGH);

  Serial.println(isNight ? "malam" : "siang");

  // Membaca nilai ADC dari LDR
  int ldr1Value = analogRead(LDR1_PIN); // Membaca LDR1
  int ldr2Value = analogRead(LDR2_PIN); // Membaca LDR2
  Serial.println(ldr1Value);
  Serial.println(ldr2Value);

  // Konversi nilai ke persentase (opsional)
  float ldr1Percent = ((4095.0 - ldr1Value) / 4095.0) * 100; // ESP32 ADC memiliki resolusi 12-bit
  float ldr2Percent = ((4095.0 - ldr2Value) / 4095.0) * 100;

  float brightnessIntensity = ldr1Percent > ldr2Percent ? ldr1Percent : ldr2Percent;
  Serial.print("Intensitas cahaya diterima: ");
  Serial.print(brightnessIntensity);
  Serial.println("%");


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
  // if (ldr1Value > ldr2Value + 100 || ldr1Value < ldr2Value - 100) {
  //   Serial.println(deg);
  //   if (ldr1Value < ldr2Value - 100 && deg > 0) deg--;
  //   else if (ldr1Value > ldr2Value + 100 && deg < 180) deg++;
  //   servo1.write(deg);
  // }

  int difference = ldr1Value - ldr2Value; // Menghitung selisih antara kedua LDR
  Serial.println(abs(difference));
  Serial.println();

  // Jika ada perbedaan signifikan antara kedua LDR
  if (abs(difference) > 500) {
    // Hitung perubahan derajat berdasarkan selisih LDR
    // Sesuaikan rentang input sesuai dengan kemungkinan selisih LDR
    // Misalnya, selisih maksimum sekitar 1023, jadi map -1023 to 1023 ke -90 to 90
    int change = map(difference, -4095, 4095, -90, 90);

    // Batasi perubahan agar servo tetap dalam rentang 0-180
    deg += change;
    if (deg < 0) {
      deg = 0;
    }
    if (deg > 125) {
      deg = 125;
    }

    // Tampilkan sudut baru
    Serial.print("Sudut Servo: ");
    Serial.println(deg);

    // Gerakkan servo ke sudut baru
    servo1.write(deg);
  }

  int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
  for (int i = 0; i < numNewMessages; i++) {
    String message = bot.messages[i].text;
    String fromName = bot.messages[i].from_name;

    Serial.println("Pesan diterima: " + message);
    if (message == "/laporan") {
      if (isNight) {
        String sensorMessage = "Intensitas cahaya yang diterima: " + String(brightnessIntensity) + "%\n\n";
        if (brightnessIntensity > 80) sensorMessage += "Persentase sangat tinggi, itu menandakan solar panel benar benar efesien dalam penerimaan cahaya dan pengumpulan daya.";
        else if (brightnessIntensity >= 50) sensorMessage += "Persentase stabil, pengisian daya sudah cukup untuk beberapa malam ke depan.";
        else if (brightnessIntensity < 50) sensorMessage += "Persentase rendah, kemungkinan cuacah sedang tidak mendukung, pengisian daya sangat lambat";
          bot.sendMessage(chatID, sensorMessage, "");
      } else {
          bot.sendMessage(chatID, "Pengisian daya terhenti, Tidak ada cahaya yang diterima saat malam!", "");
      }
    }
    else {
      bot.sendMessage(chatID, "Perintah tidak dikenali.");
    }
  }

  delay(50);

  // Tambahkan delay agar data tidak terlalu cepat muncul
  // delay(1000);
}
