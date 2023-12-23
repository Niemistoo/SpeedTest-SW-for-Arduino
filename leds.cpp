#include "leds.h"

void initializeLeds() {

pinMode(ledPin0, OUTPUT);
pinMode(ledPin1, OUTPUT);
pinMode(ledPin2, OUTPUT);
pinMode(ledPin3, OUTPUT);
}

void setLed(byte ledNumber) {
  clearAllLeds();
  
  switch (ledNumber) {
    case 0: 
      digitalWrite(ledPin0, HIGH);
      break;
    case 1: 
      digitalWrite(ledPin1, HIGH);
      break;
    case 2: 
      digitalWrite(ledPin2, HIGH);
      break;
    case 3: 
      digitalWrite(ledPin3, HIGH);
      break;
  }
}


void clearAllLeds() {

  digitalWrite(ledPin0, LOW);
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, LOW);
}

void setAllLeds() {

  digitalWrite(ledPin0, HIGH);
  digitalWrite(ledPin1, HIGH);
  digitalWrite(ledPin2, HIGH);
  digitalWrite(ledPin3, HIGH);
}

void ledIdleSequence(void) {

  uint8_t delayTime = 50;

  clearAllLeds();

  digitalWrite(ledPin0, HIGH);
  delay(delayTime);
  digitalWrite(ledPin1, HIGH);
  delay(delayTime);
  digitalWrite(ledPin0, LOW);
  delay(delayTime);
  digitalWrite(ledPin2, HIGH);
  delay(delayTime);
  digitalWrite(ledPin1, LOW);
  delay(delayTime);
  digitalWrite(ledPin3, HIGH);
  delay(delayTime);
  digitalWrite(ledPin2, LOW);
  delay(delayTime);
}

void ledFlashSequence(void) {

  clearAllLeds();
  
  delay(500);
  setAllLeds();
  delay(500);
  clearAllLeds();
  delay(500);
  setAllLeds();
  delay(500);
  clearAllLeds();
  delay(1000);
}
