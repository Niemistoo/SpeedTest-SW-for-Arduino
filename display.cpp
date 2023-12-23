#include "display.h"


void initializeDisplay(void) {

  pinMode(resetPin, OUTPUT);
  pinMode(shiftPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(outputEnablePin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}


void writeByte(uint8_t bits,bool last) {

  uint8_t numInBin[10] = {
    B11000000, 	// 0
    B11111001,	// 1
    B10100100,	// 2
    B10110000,	// 3
    B10011001,	// 4
    B10010010,	// 5
    B10000011,	// 6
    B11111000,	// 7
    B10000000,	// 8
    B10010000	  // 9
  };
  
  uint8_t data = numInBin[bits];

  digitalWrite(latchPin, LOW);

  for (int i = 0; i < 8; i++) {
    digitalWrite(dataPin, (data >> 7 - i) & 1);
    digitalWrite(shiftPin, LOW);
    digitalWrite(shiftPin, HIGH);
  }
  digitalWrite(latchPin, HIGH);

  digitalWrite(outputEnablePin, last);
}


void writeHighAndLowNumber(uint8_t tens,uint8_t ones) {

  Serial.print("SCORE: ");
  Serial.print(tens);     // Laitoin nämä, jotta voi testata koodia. Kun Serial monitorissa tulee lukuja 1 -> 99, niin tuo eka aliohjelma toimii oikein
  Serial.println(ones);

  digitalWrite(resetPin, HIGH);

  writeByte(tens, true);
  writeByte(ones, false);
  
  digitalWrite(latchPin, HIGH);
}

void showResult(byte number) {
  uint8_t tens = 0;
  uint8_t ones = 0;

  tens = number / 10;
  ones = number % 10;

  writeHighAndLowNumber(tens, ones);
}

