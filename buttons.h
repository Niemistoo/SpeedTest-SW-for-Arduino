#ifndef BUTTONS_H
#define BUTTONS_H
#include <arduino.h>
const byte buttonOnePin = 2; // First PinChangeInterrupt on D-bus
const byte buttonTwoPin = 3;
const byte buttonThreePin = 4;
const byte buttonFourPin =  5; // Last PinChangeInterrupt on D-bus
const byte startButtonPin = 7; 

/* 
  initButtonsAndButtonInterrupts subroutine is called from Setup() function
  during the initialization of Speden Spelit. This function does the following:
  1) Initializes 4 button pins for the game = Arduino pins 2,3,4,5
  2) Initializes 1 button pin for starting the game = Aruino pin 7
  3) Enables PinChangeInterrupt on D-bus in a way that interrupt
     is generated whenever some of pins 2,3,4,5,6 is connected to LOW state

*/
void initButtonsAndButtonInterrupts(void);

#endif