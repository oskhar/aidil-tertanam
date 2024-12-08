// Pin LDR
const int LDR1_PIN = 34; // Pin ADC1 untuk LDR1
const int LDR2_PIN = 35; // Pin ADC2 untuk LDR2

void setup() {
  Serial.begin(115200);
  // Konfigurasi pin sebagai input (tidak wajib karena ADC defaultnya input)
  pinMode(LDR1_PIN, INPUT);
  pinMode(LDR2_PIN, INPUT);
}

void loop() {
  // Membaca nilai ADC dari LDR
  int ldr1Value = analogRead(LDR1_PIN); // Membaca LDR1
  int ldr2Value = analogRead(LDR2_PIN); // Membaca LDR2

  // Konversi nilai ke persentase (opsional)
  float ldr1Percent = (ldr1Value / 4095.0) * 100; // ESP32 ADC memiliki resolusi 12-bit
  float ldr2Percent = (ldr2Value / 4095.0) * 100;

  // Tampilkan hasil ke Serial Monitor
  Serial.print("LDR1: ");
  Serial.print(ldr1Value);
  Serial.print(" (");
  Serial.print(ldr1Percent);
  Serial.print("%)");
  Serial.print(" | LDR2: ");
  Serial.print(ldr2Value);
  Serial.print(" (");
  Serial.print(ldr2Percent);
  Serial.println("%)");

  delay(500); // Delay untuk pembacaan berikutnya
}
