#include <Keypad.h>
// Variable untuk jumlah baris dan kolom
const byte ROWS = 4;
// 4 baris
const byte COLS = 4;
// 4 kolom
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
// Variabel untuk pin baris
byte rowPins[ROWS] = {13, 12, 14, 27};
// R1, R2, R3, R4
// Variable untuk pin kolom
byte colPins[COLS] = {26, 25, 33, 32};
// C1, C2, C3, C4
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
void setup() {  
  Serial.begin(115200); 
}
void loop() {  
  char key = keypad.getKey();   
  if (key) {     
    Serial.println(key);  
  }
}
