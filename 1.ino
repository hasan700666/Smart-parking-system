const int IR1 = 2;
const int IR2 = 3;
const int IR3 = 4;

void setup() {
  Serial.begin(9600);

  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
}

void checkIR(int pin, const char* name) {
  if (digitalRead(pin) == LOW) {
    Serial.print(name);
    Serial.println(" FULL");
  } else {
    Serial.print(name);
    Serial.println(" EMPTY");
  }
}

void loop() {
  checkIR(IR1, "IR1");
  checkIR(IR2, "IR2");
  checkIR(IR3, "IR3");

  Serial.println("------");
  delay(1000);
}