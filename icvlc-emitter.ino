#include <SoftwareSerial.h>

SoftwareSerial VLCSerial(3,2); 

void setup() {
  Serial.begin(9600);
  VLCSerial.begin(400);
  VLCSerial.print('&');
}

void loop() {
  Serial.print('A');
  VLCSerial.print('A');
  delay(1000);
}
