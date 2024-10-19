int pot = 14;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int potv = analogRead(pot);
  Serial.println(potv);
  delay(500);
}
