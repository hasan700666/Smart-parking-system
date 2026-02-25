#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myServo;

// Slot sensors
const int IR1 = 2;
const int IR2 = 3;
const int IR3 = 4;
const int IR4 = 5;
const int IR5 = 6;
const int IR6 = 7;

// Entry & Exit
const int IRI = 12;
const int IRO = 13;

int s1, s2, s3, s4, s5, s6;
bool gateOpen = false;

void setup() {
  Serial.begin(9600);

  myServo.attach(9);
  myServo.write(0);

  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);
  pinMode(IR5, INPUT);
  pinMode(IR6, INPUT);

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

  // ---- SLOT CHECK ----
  s1 = checkIR(IR1);
  s2 = checkIR(IR2);
  s3 = checkIR(IR3);
  s4 = checkIR(IR4);
  s5 = checkIR(IR5);
  s6 = checkIR(IR6);

  int totalEmpty = s1 + s2 + s3 + s4 + s5 + s6;

  Serial.print("Free Slots: ");
  Serial.println(totalEmpty);

  // ---- ENTRY ----
  if (digitalRead(IRI) == LOW && !gateOpen) {
    if (totalEmpty > 0) openGate();
    else Serial.println("PARKING FULL");
  }

  // ---- EXIT ----
  if (digitalRead(IRO) == LOW && !gateOpen) {
    openGate();
  }

  // ---- CLOSE ----
  if (gateOpen && digitalRead(IRI) == HIGH && digitalRead(IRO) == HIGH) {
    delay(1000);
    closeGate();
  }

  // ---- LCD PAGE 1 (S1–S3) ----
  lcd.setCursor(1,0);
  lcd.print("S1:");
  lcd.print(s1==0?"F":"E");
  lcd.print(" S2:");
  lcd.print(s2==0?"F":"E");
  lcd.print(" S3:");
  lcd.print(s2==0?"F":"E");

  lcd.setCursor(1,1);
  lcd.print("S4:");
  lcd.print(s4==0?"F":"E");
  lcd.print(" S5:");
  lcd.print(s5==0?"F":"E");
  lcd.print(" S6:");
  lcd.print(s6==0?"F":"E");
  delay(4000);

  // ---- LCD PAGE 2 (S4–S6) ----
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("     Free:");
  lcd.print(totalEmpty);

  lcd.setCursor(0,1);
  lcd.print("   Thank  You");
  lcd.print(" ");
  delay(2000);

  lcd.clear();
}