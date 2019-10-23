#include <TimerOne.h>
#include "Manchester.h"
#include "Channel.h"

#define SYMBOL_PERIOD 10000
#define NUM_SYMBOLS 20

#define STX 0x02
#define ETX 0x03

#define LED_PIN 2

Channel transmitCh, serialCh;

unsigned long symbols = 0;
int symbolCounter = 0;

void timerInterrupt() {
  if (symbols == 0 || symbolCounter == NUM_SYMBOLS) {
    char ch;

    if (transmitCh.get(&ch)) {
      symbols = encodeWord(ch);
    } else {
      symbols = 0x55555;
    }

    symbolCounter = 0;
  }

  if (symbols & 0x80000) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
  symbols <<= 1;
  symbolCounter++;
}

void setup() {
  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);

  Timer1.initialize(SYMBOL_PERIOD);
  Timer1.attachInterrupt(timerInterrupt);
}

void loop() {
  if (Serial.available() > 0) {
    int ch = Serial.read();

    if (ch == '\n') {
      char c;

      while (!transmitCh.put(STX)) {
        delay(1);
      }
      while (serialCh.get(&c)) {
        while (!transmitCh.put(c)) {
          delay(1);
        }
      }
      while (!transmitCh.put(ETX)) {
        delay(1);
      }
    } else {
      if (!serialCh.put(ch)) {
        serialCh.get();
        serialCh.put(ch);
      }
    }
  }
}
