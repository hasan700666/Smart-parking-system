#include <Servo.h>

Servo myServo;

void setup() {
  myServo.attach(9);   // servo signal pin connected to D9
}

void loop() {
  myServo.write(0);    // move to 0 degrees
  delay(1000);         // wait 1 second

  myServo.write(90);   // move to 90 degrees
  delay(1000);         // wait 1 second
}