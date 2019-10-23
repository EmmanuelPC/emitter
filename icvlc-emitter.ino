#define LED_PIN 2

void setup() {
  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    int ch = Serial.read();

    if (ch == '0') {
      digitalWrite(LED_PIN, LOW);
    } else if (ch == '1') {
      digitalWrite(LED_PIN, HIGH);
    }
  }
}
