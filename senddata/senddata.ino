#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

const char* ssid = "Redmi Note 11";
const char* password = "punyaaku";
const char* botToken = "7928981214:AAGO7AJnLuSxZBPoriQzr1mlaXO2dL_Bh9U";
const char* chatID = "1311526288";
const int lampPin = 2;

WiFiClientSecure client;
UniversalTelegramBot bot(botToken, client);

void setup() {
  Serial.begin(115200);

  pinMode(lampPin, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Mencoba menghubungkan ke WiFi...");
  }
  Serial.println("Terhubung ke WiFi!");

  client.setInsecure();  
  bot.sendMessage(chatID, "Bot Telegram sudah terhubung dengan ESP32!", "");
}

void loop() {
  int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

  for (int i = 0; i < numNewMessages; i++) {
    String message = bot.messages[i].text;  
    String fromName = bot.messages[i].from_name;  

    Serial.println("Pesan diterima: " + message);
    
    if (message == "/on") {
      digitalWrite(lampPin, HIGH);  
      bot.sendMessage(chatID, "Lampu telah dinyalakan!", "");
    }
    
    else if (message == "/off") {
      digitalWrite(lampPin, LOW);  
      bot.sendMessage(chatID, "Lampu telah dimatikan!", "");
    }
    else {
      bot.sendMessage(chatID, "Perintah tidak dikenali. Gunakan /on untuk menyalakan lampu atau /off untuk mematikan lampu.", "");
    }
  }

  delay(1000);  
}
