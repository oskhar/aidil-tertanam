int relay = 27;

void setup(){
  pinMode(relay, OUTPUT);
  digitalWrite(relay, LOW);
  delay(2000);
}

void loop(){
  digitalWrite(relay, LOW);
  delay(2000);
  digitalWrite(relay, HIGH);
  delay(2000);

}