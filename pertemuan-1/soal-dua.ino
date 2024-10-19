const int LedPin = 18; // Pin untuk LED 1
const int BuzzerPin = 33; // Pin untuk LED 2 (pastikan ini adalah pin output yang valid pada ESP32)
const int ButtonPin = 14;

int buttonState = 0;
int pressCount = 0;        // Menghitung jumlah tekan button
bool isActive = false;       // Variabel untuk menghitung jumlah kedipan LED 1

void setup() {
  Serial.begin(9600);
  pinMode(LedPin, OUTPUT);
  pinMode(BuzzerPin, OUTPUT);
  pinMode(ButtonPin, INPUT_PULLUP);

  digitalWrite(LedPin, LOW);
  digitalWrite(BuzzerPin, LOW);
}

void loop() {
  // Baca status button
  buttonState = digitalRead(ButtonPin);

  // Jika button ditekan (status LOW), dan status sebelumnya tidak ditekan
  if (buttonState == HIGH && isActive == false) {
    isActive = true;
    if (pressCount == 1){
      digitalWrite(LedPin, HIGH);  // LED menyala
      digitalWrite(BuzzerPin, LOW); // Buzzer mati
    } else if (pressCount == 2){
      digitalWrite(LedPin, LOW);   // LED mati
      digitalWrite(BuzzerPin, HIGH); // Buzzer menyala
    } else if (pressCount == 3){
      digitalWrite(LedPin, HIGH);  // LED menyala
      digitalWrite(BuzzerPin, HIGH); // Buzzer menyala
    }  else {
      digitalWrite(LedPin, LOW);   // LED mati
      digitalWrite(BuzzerPin, LOW); // Buzzer mati
    }
    pressCount++;
  } else if (buttonState == LOW && isActive == true) {
    isActive = false; 
  }

  delay(50);
}

