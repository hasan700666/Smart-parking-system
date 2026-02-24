#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo myServo;

const int IR1 = 2;
const int IR2 = 3;
const int IR3 = 5;  // checking sensor

int slot1;
int slot2;

void setup() {
  Serial.begin(9600);

  myServo.attach(9);

  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
}

// ✅ function must return int
int checkIR(int pin, const char* name) {
  if (digitalRead(pin) == LOW) {
    Serial.print(name);
    Serial.println(" FULL");
    return 0;   // slot occupied
  } else {
    Serial.print(name);
    Serial.println(" EMPTY");
    return 1;   // slot free
  }
}

int checkIRforDisplay(int pin) {
  if (digitalRead(pin) == LOW) {
    return 0;   // slot occupied
  } else {
    return 1;   // slot free
  }
}

void loop() {

  if (digitalRead(IR3) == LOW) {
    Serial.println("CAR IS WAITING FOR ENTER");
    Serial.println("------");
    slot1 = checkIR(IR1, "IR1");
    slot2 = checkIR(IR2, "IR2");
    Serial.println("------");

    int totalEmpty = slot1 + slot2;

    Serial.print("Available Slots: ");
    Serial.println(totalEmpty);

    if (totalEmpty == 0) {
      Serial.println("PARKING FULL - GATE CLOSED");
      myServo.write(0);
    } else {
      Serial.println("SPACE AVAILABLE - GATE OPEN");
      myServo.write(90);
      delay(5000);
      myServo.write(0);
      Serial.println("GATE CLOSED");
    }
    delay(2000);
    lcd.init();
    lcd.backlight();

    if (checkIRforDisplay(IR1) == 0){
      lcd.setCursor(0,0);
      lcd.print("S-1-F");
    }
    else {
      lcd.setCursor(0,0);
      lcd.print("S-1-E");
    }
    if (checkIRforDisplay(IR2) == 0){
      lcd.setCursor(6,0);
      lcd.print("S-2-F");
    }
    else {
      lcd.setCursor(6,0);
      lcd.print("S-2-E");
    }

    lcd.setCursor(0,1);
    lcd.print("The Project");
  }

  else {
    Serial.println("NO CAR ENTERING");
    Serial.println("------");
    delay(2000);
  }
}
