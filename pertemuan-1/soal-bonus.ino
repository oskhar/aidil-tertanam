const int LedPin1 = 32; // Pin untuk LED 1
const int LedPin2 = 33; // Pin untuk LED 2 (pastikan ini adalah pin output yang valid pada ESP32)
int counting = 1;       // Variabel untuk menghitung jumlah kedipan LED 1

void setup() {
  Serial.begin(9600);
  pinMode(LedPin1, OUTPUT);
  pinMode(LedPin2, OUTPUT);
}

void loop() {
  // Kedipkan LED 1 sebanyak 10 kali
  while (counting < 10) {
    Serial.print("LED 1 berkedip sebanyak: ");
    Serial.println(counting);     // Tampilkan jumlah kedipan pada Serial Monitor

    digitalWrite(LedPin1, HIGH);  // Nyalakan LED 1
    delay(500);                   // Tunggu 0.5 detik
    digitalWrite(LedPin1, LOW);   // Matikan LED 1
    delay(500);                   // Tunggu 0.5 detik

    counting++;                   // Tambah hitungan kedipan
  }

  // Setelah LED 1 berkedip 10 kali, nyalakan LED 2
  if (counting == 10) {
    Serial.println("LED 1 selesai berkedip. Menyalakan LED 2.");
    digitalWrite(LedPin1, HIGH);  // Nyalakan LED 1
    digitalWrite(LedPin2, HIGH);  // Nyalakan LED 2

    delay(500);                   // Tunggu 0.5 detik

    digitalWrite(LedPin1, LOW);   // Nyalakan LED 1

    counting++;                   // Tambah hitungan kedipan
  }
}

