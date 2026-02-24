const int IR_PIN = 2;   // connect IR OUT to pin 2

void setup() {
  Serial.begin(9600);
  pinMode(IR_PIN, INPUT);
}

void loop() {
  int sensorValue = digitalRead(IR_PIN);
  if (sensorValue == LOW) {
    Serial.println("IR Sensor: FULL (Object Detected)");
  } else {
    Serial.println("IR Sensor: EMPTY (No Object)");
  }
  delay(500);
}
