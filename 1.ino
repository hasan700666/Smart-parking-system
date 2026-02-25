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

void setup() {
  Serial.begin(9600);

  myServo.attach(9);
  myServo.write(0);   // gate closed

  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IRI, INPUT);
  pinMode(IRO, INPUT);

  lcd.init();        // ✅ only once
  lcd.backlight();
}

int checkIR(int pin, const char* name) {
  if (digitalRead(pin) == LOW) {
    Serial.print(name);
    Serial.println(" FULL");
    return 0;
  } else {
    Serial.print(name);
    Serial.println(" EMPTY");
    return 1;
  }
}

int checkIRforDisplay(int pin) {
  if (digitalRead(pin) == LOW) return 0;
  else return 1;
}

void loop() {

  // -------- SLOT CHECK --------
  slot1 = checkIR(IR1, "IR1");
  slot2 = checkIR(IR2, "IR2");

  int totalEmpty = slot1 + slot2;

  Serial.print("Available Slots: ");
  Serial.println(totalEmpty);
  Serial.println("------");

  // -------- ENTRY LOGIC --------
  if (digitalRead(IRI) == LOW) {
    Serial.println("CAR WAITING");

    if (totalEmpty > 0) {
      Serial.println("OPEN GATE");
      myServo.write(90);

      // wait until car passes exit sensor
      while (digitalRead(IRO) == HIGH) {
        Serial.println("GATE OPEND");
        delay(1000);
      }

      delay(1000);
      myServo.write(0);
      Serial.println("GATE CLOSED");
    } else {
      Serial.println("PARKING FULL");
    }
  }

  // -------- LCD DISPLAY --------
  if (checkIRforDisplay(IR1) == 0) {
    lcd.setCursor(0,0);
    lcd.print("S1:F ");
  } else {
    lcd.setCursor(0,0);
    lcd.print("S1:E ");
  }

  if (checkIRforDisplay(IR2) == 0) {
    lcd.setCursor(8,0);
    lcd.print("S2:F ");
  } else {
    lcd.setCursor(8,0);
    lcd.print("S2:E ");
  }

  lcd.setCursor(0,1);
  lcd.print("Free:");
  lcd.print(totalEmpty);
  lcd.print("  ");

  delay(500);
}