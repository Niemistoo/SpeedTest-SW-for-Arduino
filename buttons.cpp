#include "buttons.h"

void initButtonsAndButtonInterrupts(void) {
  
  PCICR |= B00000100;
  PCMSK2 |= B10111100;
  
  pinMode(buttonOnePin, INPUT_PULLUP);     //Game Button 1
  pinMode(buttonTwoPin, INPUT_PULLUP);     //Game Button 2
  pinMode(buttonThreePin, INPUT_PULLUP);   //Game Button 3
  pinMode(buttonFourPin, INPUT_PULLUP);    //Game Button 4
  pinMode(startButtonPin, INPUT_PULLUP);   //Start Button
}