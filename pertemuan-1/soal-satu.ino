// Definisi pin LED dan Buzzer
const int led1Pin = 2;    // Pin LED 1
const int led2Pin = 4;    // Pin LED 2
const int buzzer1Pin = 17; // Pin Buzzer 1
const int buzzer2Pin = 18; // Pin Buzzer 2
void setup() {
  // Atur pin sebagai output
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(buzzer1Pin, OUTPUT);
  pinMode(buzzer2Pin, OUTPUT);
  digitalWrite(buzzer1Pin, LOW);
  digitalWrite(buzzer2Pin, LOW);
}

void loop() {
  digitalWrite(led1Pin, LOW);
  digitalWrite(buzzer1Pin, LOW);
  digitalWrite(led2Pin, HIGH);
  digitalWrite(buzzer2Pin, HIGH);
  delay(3500);
  digitalWrite(led2Pin, LOW);
  digitalWrite(buzzer2Pin, LOW);
  digitalWrite(led1Pin, HIGH);
  digitalWrite(buzzer1Pin, HIGH);
  delay(3500);
}