#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Change address to 0x27 or 0x3F if needed
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();       
  lcd.backlight();  

  lcd.setCursor(0, 0);   // column 0, row 0
  lcd.print("Wel");

  lcd.setCursor(4, 0);   // column 0, row 0
  lcd.print("co");

  lcd.setCursor(8, 0);   // column 0, row 0
  lcd.print("me");

  lcd.setCursor(0, 1);   // column 0, row 1
  lcd.print("To Project");
}

void loop() {
  // nothing needed here
}