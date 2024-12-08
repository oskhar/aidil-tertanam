int Potensiometer = 14;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int PotensiometerValue = analogRead(Potensiometer);
  Serial.println(PotensiometerValue);
  delay(500);
}
