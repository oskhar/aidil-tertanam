// LATIHAN SOAL UTS SISTEM BENAM

// 1. Button + 2 LED + LCDBuatlah sebuah rangkaian ketika button ditekan, setiap jumlah button ditekan ganjil maka 1 LED akan menyala dan LCD menampilkan tulisan "Ganjil", jika genap maka 2 LED akan menyala dan LCD menampilkan tulisan "Genap", jika merupakan kelipatan 5 maka semua LED mati dan LCD menampilkan tulisan "Alip Ganteng”

// JAWABAN 1

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int Lampu1 = 5;
int Lampu2 = 17;
int button = 4;
int buttonState = 0;
int lastButtonState = 0;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
int buttonPressCount = 0;

void setup (){
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.clear();
  pinMode(button, INPUT);
  pinMode(Lampu1, OUTPUT);
  pinMode(Lampu2, OUTPUT);
}

void loop() {
  int reading = digitalRead(button);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == HIGH) {
        buttonPressCount++;
        if (buttonPressCount % 5 == 0) {
          digitalWrite(Lampu1, LOW);
          digitalWrite(Lampu2, LOW);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Alip Ganteng");
        } else if (buttonPressCount % 2 == 0) {
          digitalWrite(Lampu1, HIGH);
          digitalWrite(Lampu2, HIGH);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Genap");
        } else {
          digitalWrite(Lampu1, HIGH);
          digitalWrite(Lampu2, LOW);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Ganjil");
        }
      }
    }
  }

  lastButtonState = reading;
}



// JAWABAN 2

#include <Wire.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 16, 1);


int led1 = 27;
int led2 = 26;
int button = 25;
int buttonState = 0;
int lastButtonState = 0;
int counter = 0;


void setup() {
  pinMode (led1, OUTPUT);
  pinMode (led2, OUTPUT);
  pinMode (button, INPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.clear();
}


void loop() {
  buttonState = digitalRead (button);


  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      counter++;
      if (counter > 4) {
        counter = 0;
      }
      switch (counter) {
        case 0:
        lcd.clear();
        digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
        lcd.print("Alip Ganteng");
        break;


        case 1:
        lcd.clear();
        digitalWrite(led1, HIGH);
        digitalWrite(led2, LOW);
        lcd.print("Ganjil");
        break;


        case 2:
        lcd.clear();
        digitalWrite(led1, HIGH);
        digitalWrite(led2, HIGH);
        lcd.print("Genap");
        break;


        case 3:
        lcd.clear();
        digitalWrite(led1, HIGH);
        digitalWrite(led2, LOW);
        lcd.print("Ganjil");
        break;


        case 4:
        lcd.clear();
        digitalWrite(led1, HIGH);
        digitalWrite(led2, HIGH);
        lcd.print("Genap");
        break;
      }
    }
    delay(50);
  }
  lastButtonState = buttonState;
}

// catatan : masalah dari jawaban 2 adalah pembuatan casenya manual, yang udah ada di code itu baru sampe 5 aja. Lupa kalo setelah 5 itu angkanya genap bukan ganjil

// 2. Potensiometer + Button + LCD I2CBuatlah sebuah rangkaian di mana nilai potensiometer akan disimpan ketika button ditekan. Setiap kali button ditekan, nilai potensiometer terbaru akan disimpan dan ditampilkan pada LCD I2C dengan format “Nilai Terakhir: {nilai}”.

// JAWABAN 1

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int pot = 33;
const int button = 25;
int potValue = 0;
bool lastButtonState = HIGH; // Status button sebelumnya (default HIGH karena pull-up)
bool buttonPressed = false; // Menyimpan apakah button telah ditekan

void setup() {
  pinMode (button, INPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Nilai terakhir: ");
  lcd.setCursor(0, 1);
  lcd.print(potValue);
}

void loop() {
  bool currentButtonState = digitalRead(button);  // Membaca status button saat ini
 
  // Hanya mendeteksi ketika button ditekan (transisi dari HIGH ke LOW)
  if (lastButtonState == HIGH && currentButtonState == LOW) {
    buttonPressed = true;  // Button telah ditekan
  }

  // Jika buttonPressed true, baca nilai potensiometer dan tampilkan
  if (buttonPressed) {
    potValue = analogRead(pot);  // Membaca nilai potensiometer
    potValue = map(potValue, 0, 1023, 0, 100);  // Mengubah rentang nilai menjadi 0-100
    lcd.clear();  // Menghapus layar
    lcd.setCursor(0, 0);
    lcd.print("Nilai Terakhir:");
    lcd.setCursor(0, 1);
    lcd.print(potValue);  // Menampilkan nilai terbaru
    buttonPressed = false;  // Reset flag setelah nilai diperbarui
  }

  lastButtonState = currentButtonState;  // Simpan status button sebelumnya
}


// JAWABAN 2

#include <LiquidCrystal_I2C.h>
#include <Wire.h>


LiquidCrystal_I2C lcd(0x27, 16,2);


int pot = 14;
int button = 4;
int buttonState = 0;
int lastButtonState = 0;
int potv = 0;


void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);


  pinMode(button, INPUT);
}


void loop() {
  buttonState = digitalRead(button);


  Serial.println(potv);


  if(buttonState == 1 && lastButtonState == 0){
      potv = analogRead(pot);


      lcd.clear();
      lcd.print("Nilai terakhir: ");


      lcd.setCursor(0,1);
      lcd.print (potv);
  }
 
  // Simpan status tombol terakhir
  lastButtonState = buttonState;
}

// 3.  Buzzer + Sensor Suara + LCD. Rancang sistem di mana buzzer berbunyi ketika sensor suara mendeteksi suara di atas ambang batas tertentu. LCD akan menampilkan "Suara Terdeteksi" setiap kali suara terdeteksi.  (Sensor suara yg kita punya cuma bisa DO)

// JAWABAN 1

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Buzzer
// Sensor suara
// LCD

LiquidCrystal_I2C lcd(0x27, 16, 2);

int buzzer = 5; // Pin untuk buzzer
int sensor = A0; // Pin untuk sensor suara (analog)
int ambangSuara = 500; // Ambang batas suara

void setup() {
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW); // Pastikan buzzer mati di awal

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Tes!");

  Serial.begin(9600); // Untuk debug
}

void loop() {
  int sensorValue = analogRead(sensor); // Baca nilai analog dari sensor suara
  //kalo make digitalRead ga bisa nentuin nilai kekerasan suaranya
  //cuma bisa LOW (ga ada suara) atau HIGH (ada suara)

  // Jika suara di atas ambang batas
  if (sensorValue > ambangSuara) {
    Serial.println("Suara Terdeteksi");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Suara Terdeteksi");

    // Jika suara cukup keras, hidupkan buzzer
    digitalWrite(buzzer, HIGH);
  } else {
    Serial.println("Suara Tidak Terdeteksi");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Suara Tidak Terdeteksi");

    // Matikan buzzer
    digitalWrite(buzzer, LOW);
  }

  delay(100); // Tambahkan sedikit delay untuk menghindari flickering
}
// 4.  (Potensiometer + Motor Servo + LCD) Gunakan potensiometer untuk mengontrol sudut dari motor servo, dan tampilkan sudut tersebut pada LCD. Ketika potensiometer diubah, LCD akan menampilkan "Sudut Servo: {sudut}. 

// Jawaban:

#include<ESP32Servo.h>

#define PIN_POTENTIOMETER 35
#define PIN_SERVO 22

int button = 15;
int counter = 1;
int status;
int angle;

Servo servo1;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(button, INPUT_PULLUP);
  servo1.attach(PIN_SERVO);
}



void loop() {
  int analogValue = analogRead(PIN_POTENTIOMETER);
  status = digitalRead(button);

  if(status == 0) {
    counter++;
  }

  if(counter > 3) {
    counter = 1;  // Reset counter jika lebih dari 3
  }

  delay(150);  // Debounce untuk tombol


  // put your main code here, to run repeatedly:
  // Bikin Fungsi Button
  if (counter == 1) {
    angle = map(analogValue, 0,  4095, 0,  180);
    servo1.write(angle);
    Serial.println("Ganjil");
  } else if (counter == 2) {
    angle = map(analogValue, 0,  4095, 180,  0);
    servo1.write(angle);
    Serial.println("Genap");
  } else {
    Serial.println("Pengkodisian Sudah Selesai");
  }
}





// 5. (Ultrasonik + Buzzer + LCD) Rancang sistem yang menggunakan sensor ultrasonik untuk mendeteksi objek dalam jarak 10 cm. Jika objek terdeteksi, buzzer akan berbunyi, dan LCD menampilkan "Objek Terdeteksi. 
// 6. Button + Potensiometer + LED Buat rangkaian dengan tombol dan potensiometer. Ketika tombol ditekan, LED akan menyala dengan kecerahan yang sesuai dengan nilai dari potensiometer.  (Intensitas keterangan Lampu ga akan keluar)

int pot = 14;
int button = 23;
int led = 15;
int buttonState = 0;
int lastButtonState = 0;
int potv = 0;

void setup() {
  pinMode(button, INPUT);
  pinMode(led, OUTPUT);

  digitalWrite(led, LOW);
 
  Serial.begin(9600);
}

void loop() {
  buttonState = digitalRead(button);

  potv = analogRead(pot);

  Serial.println(potv);

  if(buttonState == 1 && lastButtonState == 0 || potv > 1000){
    digitalWrite(led, HIGH);
  }else if(buttonState == 0 && lastButtonState == 1 || potv < 1000){
    digitalWrite(led, LOW);
  }
 
  // Simpan status tombol terakhir
  lastButtonState = buttonState;
}

// 7. Buatlah rangkaian DHT, LCD dan LED. LCD dapat Menampilkan Kelembaban pada baris ke 1 yang nilai nya didapat dari sensor DHT, dan pada baris kedua Menampilkan suhu DHT dalam format celcius, dan pada saat suhu nya sangat tinggi maka LED akan menyala.

// Jawaban:

#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
#define DHTPIN 13
#define DHTTYPE 22
int lampu1 = 4;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
 lcd.init();
 lcd.backlight();
 lcd.setCursor(0,0);
 Serial.begin(9600);
 Serial.println(F("DHT 22 TEST"));
 dht.begin();
 pinMode(lampu1, OUTPUT);
 digitalWrite(lampu1, LOW);
}

void loop() {
  delay(2000);
  // float h = dht.readHumidity();
  float t = dht.readTemperature();
  // float f = dht.readTemperature(true);

  if (isnan(t)) {
    Serial.println(F("Failed to read from DHT Sensor!"));
    return;
  }

  // lcd.print("Humidity:");
  // lcd.print(h);
  lcd.println("Temperature:");
  lcd.print(t);
  lcd.print("C");
  // lcd.print(f);
  // lcd.print("F");
  // put your main code here, to run repeatedly:
  if (t > 33) {
    digitalWrite(lampu1, HIGH);
  } else {
    digitalWrite(lampu1, LOW);

  }

}

// 8. Buatlah rangkaian 2 LED, Button, LCD. LCD Dapat Menampilkan Nilai Angka Ketika Angka Pada LCD Bernilai Genap Maka LED 1 akan Menyala jika Angka Bernilai Ganjil Maka LED 2 akan Menyala dan Ketika Nilai nya pada LCD bernilai 10 LED 1 dan LED 2 akan Menyala.

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int Lampu1 = 15;
int Lampu2 = 16;
int button = 23;
int buttonState = 0;
int lastButtonState = 0;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
int buttonPressCount = 0;

void setup (){
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.clear();
  pinMode(button, INPUT);
  pinMode(Lampu1, OUTPUT);
  pinMode(Lampu2, OUTPUT);
}

void loop() {
  int reading = digitalRead(button);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == HIGH) {
        buttonPressCount++;
        if (buttonPressCount % 10 == 0) {
          digitalWrite(Lampu1, HIGH);
          digitalWrite(Lampu2, HIGH);
          lcd.clear();
          lcd.setCursor(7, 0);
          lcd.print("10");
        } else if (buttonPressCount % 2 == 0) {
          digitalWrite(Lampu1, LOW);
          digitalWrite(Lampu2, HIGH);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Genap");
        } else {
          digitalWrite(Lampu1, HIGH);
          digitalWrite(Lampu2, LOW);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Ganjil");
        }
      }
    }
  }

  lastButtonState = reading;
}

// 9. Buatlah Rangkaian Servo, LCD, Button. Pada awalnya nilai derajat pada servo adalah 0, dan setiap button ditekan derajat pada servo akan bertambah 45 dan setiap derajat pada servo bernilai 180 maka setelah 3 detik dia akan kembali ke 0, dan setiap nilai tersebut ditampilkan pada LCD.
// 10. Buatlah rangkaian Servo, Button, dan Potensiometer. Button dipencet counter nambah 1, jika counter ganjil servo searah potensiometer, jika genap servo berlawanan arah.

// JAWABAN 1

#include<ESP32Servo.h>

#define PIN_POTENTIOMETER 14
#define PIN_SERVO 15

int button = 25;
int counter = 1;
int status;
int angle;

Servo servo1;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(button, INPUT);
  servo1.attach(PIN_SERVO);
}



void loop() {
  int analogValue = analogRead(PIN_POTENTIOMETER);
  status = digitalRead(button);

  if(status == 1) { //kondisi awal button 0 atau pinout sejajar GND
    counter++;
    Serial.println(counter);
  }

  if(counter > 3) {
    counter = 1;  // Reset counter jika lebih dari 3
  }

  delay(150);  // Debounce untuk tombol


  // put your main code here, to run repeatedly:
  // Bikin Fungsi Button
  if (counter == 1) {
    angle = map(analogValue, 0,  4095, 0,  180);
    servo1.write(angle);
    Serial.println("Ganjil");
  } else if (counter == 2) {
    angle = map(analogValue, 0,  4095, 180,  0);
    servo1.write(angle);
    Serial.println("Genap");
  } else {
    Serial.println("Pengkodisian Sudah Selesai");
  }
}



