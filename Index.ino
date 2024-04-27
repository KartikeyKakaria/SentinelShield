#include <Keypad.h>;
const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};
int BuzzPin = 11;
int LedPin = 12;


String Password = "";
String enteredPassword = "";
bool AccessGranted = false;
bool PasswordSet = false;
bool startBuzz = false;

byte rowPins[ROWS] = { 2, 3, 4, 5 };
byte colPins[COLS] = { A0, A1, A2, A3 };
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(BuzzPin, OUTPUT);
  pinMode(LedPin, OUTPUT);
  Serial.println("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
  Serial.println("SET PASSWORD: ");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(startBuzz){
    digitalWrite(BuzzPin, HIGH);
  }else{
    digitalWrite(BuzzPin, LOW);
  }
  if(AccessGranted){
    digitalWrite(BuzzPin, LOW);
    digitalWrite(LedPin, HIGH);
  }else{
    if(PasswordSet){

      digitalWrite(LedPin, LOW);
    }
  }
  String customKey = String(customKeypad.getKey());
  if (customKey) {
    if (PasswordSet) {
      if (customKey == "*") {
        if (enteredPassword == Password) {
          Serial.println("ACCESS GRANTED");
          Serial.println(enteredPassword);
          enteredPassword = "";
          AccessGranted = true;
          startBuzz = false;
        } else {
          Serial.println("ACCESS DENIED");
          Serial.println(enteredPassword);
          startBuzz = true;
          enteredPassword = "";
          AccessGranted = false;
        }
      } else {
        enteredPassword += customKey;
      }

    } else {
      if (customKey == "*") {
        if (Password != "") {
          Serial.println("PASSWORD SET! ");
          Serial.println(Password);
          PasswordSet = true;
        }
      } else {
        Password += customKey;
      }
    }
  }
}
