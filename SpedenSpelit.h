#ifndef SPEDENSPELIT_H
#define SPEDENSPELIT_H
#include <arduino.h>

volatile uint8_t userInput;           // Variable for pin number of most recent pressed button 
volatile uint8_t currentScore;        // Variable for score
volatile uint8_t highScore;           // Variable holds highest score since arduino reset
volatile uint8_t randomNumber;        // Variable which holds generated randomNumber. This value is which led will turn on and the value saved in randomNumbers[] list
volatile uint8_t nextRandomNumber;    // Value used to control list of randomNumber index
volatile uint8_t pressCounter;        // Counts how many times user has pressed button. This value is used to compare to check same index value between randomNumbers and userNumbers

volatile bool gameIsOn;           // Boolean value to check if the game is running
volatile bool buttonPressed;      // Boolean value to check if button is pressed. Value is set to false after checkGame() function
volatile bool runStartSequence = false;


volatile uint8_t randomNumbers[100];  // List of random generated numbers the player must press in order
volatile uint8_t userNumbers[100];    // List of pressed numbers by user

volatile unsigned long int buttonMillis;         // Variable to save millis() time when button is pressed
volatile int lastButtonReading;   // Variable to save the last reading from a button press (For debouncing)


/*
  initializeTimer() subroutine intializes Arduino Timer1 module to
  give interrupts at rate 1Hz
  
*/
void initializeTimer(void);


/*
  initializeGame() subroutine is used to initialize all variables
  needed to store random numbers and player button push data.
  This function is called from startTheGame() function.
  
*/
void initializeGame(void);

/*
  checkGame() subroutine is used to check the status
  of the Game after each player button press.
  
  If the latest player button press is wrong, the game stops
  and if the latest press was right, game display is incremented
  by 1.
  
  Parameters
  byte lastButtonPress of the player 0 or 1 or 2 or 3
  
*/
void checkGame(byte);


/*
  startTheGame() subroutine calls InitializeGame()
  function and enables Timer1 interrupts to start
  the Game.
*/
void startTheGame(void);

/*
  generateRandomNumber() generates a random number between 0-3 and returns it
*/
int generateRandomNumber(void);


void startTimer(void);

void stopTimer(void);

#endif