#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

const char* ssid = "Nomi";
const char* password = "hardanti";

// Buat Bot dari Telegram @BotFather
const char* botToken = "7619060354:AAExXAAeEZZkwtAKf2LgyOO6eJXVPGcZPA0";

// Check chat id dari Telegram 
const char* chatID = "5807149704";

WiFiClientSecure client;
UniversalTelegramBot bot(botToken, client);

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Mencoba menghubungkan ke WiFi...");
  }
  Serial.println("Terhubung ke WiFi!");

  client.setInsecure();  

  bot.sendMessage(chatID, "ESP32 sudah terhubung dengan Telegram!", "");
}

void loop() {
}
