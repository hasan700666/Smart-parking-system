#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myServo;

const int IR1 = 2;
const int IR2 = 3;
const int IRI = 12;   // entry sensor
const int IRO = 13;   // exit sensor

int slot1;
int slot2;

bool gateOpen = false;

void setup() {
  Serial.begin(9600);

  myServo.attach(9);
  myServo.write(0);

  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IRI, INPUT);
  pinMode(IRO, INPUT);

  lcd.init();
  lcd.backlight();
}

int checkIR(int pin) {
  if (digitalRead(pin) == LOW) return 0;
  else return 1;
}

void openGate() {
  myServo.write(90);
  gateOpen = true;
  Serial.println("GATE OPEN");
}

void closeGate() {
  delay(4000);
  myServo.write(0);
  gateOpen = false;
  Serial.println("GATE CLOSED");
}

void loop() {

  // ---- SLOT STATUS ----
  slot1 = checkIR(IR1);
  slot2 = checkIR(IR2);
  int totalEmpty = slot1 + slot2;

  Serial.print("Free: ");
  Serial.println(totalEmpty);

  // ---- ENTRY EVENT ----
  if (digitalRead(IRI) == LOW && !gateOpen) {
    if (totalEmpty > 0) {
      openGate();
    } else {
      Serial.println("PARKING FULL");
    }
  }

  // ---- EXIT EVENT ----
  if (digitalRead(IRO) == LOW && !gateOpen) {
    openGate();
  }

  // ---- CLOSE CONDITION ----
  if (gateOpen && digitalRead(IRI) == HIGH && digitalRead(IRO) == HIGH) {
    delay(1000);
    closeGate();
  }

  // ---- LCD ----
  lcd.setCursor(0,0);
  lcd.print("S1:");
  lcd.print(slot1 == 0 ? "F" : "E");

  lcd.setCursor(8,0);
  lcd.print("S2:");
  lcd.print(slot2 == 0 ? "F" : "E");

  lcd.setCursor(0,1);
  lcd.print("Free:");
  lcd.print(totalEmpty);
  lcd.print("   ");

  delay(300);
}