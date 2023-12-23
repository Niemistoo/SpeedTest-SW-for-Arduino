#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "melody.h"
#include "SpedenSpelit.h"

void setup() {

  Serial.begin(9600);                 // Enable Serial printing
  playMelody();                       // Play melody on startup
  initButtonsAndButtonInterrupts();   // Initializes buttons and button interrupts
  initializeGame();                   // Initializes all modules. Enables score "00" on display
}

void loop() {
  if (runStartSequence) {             // If start button is pressed
    currentScore = 0;
    showResult(currentScore);         // Set display to show "00" on start
    ledFlashSequence();               // Run led sequence 
    startTheGame();
    runStartSequence = false;         // Change start bool state
  }

  else if (buttonPressed && gameIsOn) {    // If game is running and player has pressed a button
    checkGame(userInput);                  // Call for checkGame() function and pass pressed button number as parameter (0-3)
  }

  else if (!runStartSequence && !gameIsOn) {  // If game is not on
    ledIdleSequence();

  }
}

ISR(PCINT2_vect) {

  if (millis()>buttonMillis+2){                                           // Disables button debounce

    if (digitalRead(buttonOnePin) == LOW && (lastButtonReading == 1)){    // If buttonX is pressed and lastButtonReading = 1
      Serial.println("Pressed button 1");                                 // Prints a message to Serial port
      userInput = 0;                                                      // Sets value for userInput
      lastButtonReading = 0;                                              // Sets lastButtonReading back to 0;
      buttonPressed = true;                                               // Sets buttonPressed boolean value as true
    }
    else if (digitalRead(buttonTwoPin) == LOW && (lastButtonReading == 1)){
        Serial.println("Pressed button 2");
        userInput = 1;
        lastButtonReading = 0;
        buttonPressed = true;
    }
    else if (digitalRead(buttonThreePin) == LOW && (lastButtonReading == 1)){
        Serial.println("Pressed button 3");
        userInput = 2;
        lastButtonReading = 0;
        buttonPressed = true;
    }
    else if (digitalRead(buttonFourPin) == LOW && (lastButtonReading == 1)){
        Serial.println("Pressed button 4");
        userInput = 3;
        lastButtonReading = 0;
        buttonPressed = true;
    }
     else if (digitalRead(startButtonPin) == LOW && (lastButtonReading == 1)){ 
        stopTimer();                  // Stops microcontroller timer during the intro sequence
        Serial.println("Pressed Start button");     
        gameIsOn = false;             // Disables gameIsOn bolean during the intro sequence
        runStartSequence = true;      // Sets Bolean value for intro sequence
        lastButtonReading = 0;        // Sets lastButtonReading to 0
    }
    else{
      // Didn't enter any if statement because lastButtonReading was 0
      
      lastButtonReading = 1;          // Sets lastButtonReading back to 1 so next 
    }
  }
  buttonMillis = millis();            // Saving the current interrupt time in the variable 
}

ISR(TIMER1_COMPA_vect) {                              // Timer interrupt generates a random number that is used to set certain led.

  if (gameIsOn) {
    randomNumber = generateRandomNumber();            // Generate a random number
    if (nextRandomNumber < 99) {
      while (nextRandomNumber != 0 && randomNumber == randomNumbers[nextRandomNumber -1]) { // Checks if the generated number is same as previous
        randomNumber = generateRandomNumber();
      }
      randomNumbers[nextRandomNumber] = randomNumber; // Add generated number to list
      nextRandomNumber += 1;                          // +1 to randomNumber amount
      setLed(randomNumber);                           // Turns the led on
      OCR1A *= 0.98;                                  // Increase speed 2% on every interrupt cycle
    }
  }
}

void initializeTimer(void) {

  TCCR1A = 0;                         // Set 0 to not to use pins 10 and 11 for timer
  TCCR1B = 0x0C;                      // 16MHz / 256 = 62 500 pulse /sec
  OCR1A = 62500;                      // This register sets comparsion value. When this many clock pulses is counted, interrupt happens (62 500 / 62 500 = 1Hz)
  TIMSK1 = 0x00;                      // OCIE1A Enabled When this bit is written to one, and the I-flag in the Status Register is set (interrupts globally enabled), the Timer/Counter1 Output Compare A Match interrupt is enabled
}

void checkGame(byte nbrOfButtonPush) {

  userNumbers[pressCounter] = nbrOfButtonPush;  // Add pressed number to list

  if (userNumbers[pressCounter] == randomNumbers[pressCounter]) { // Checks if right button was pressed as the game generated number in same index
    Serial.println("Oikein");
    pressCounter += 1;                // Increments pressCounter by 1. This keeps count of index for checking the game
    currentScore += 1;                // Increments score by 1
    buttonPressed = false;            // Initializes boolean value to enable next press
    showResult(currentScore);

  } else {

    if (currentScore > highScore) {   // Set if new score is highscore
      highScore = currentScore;
    }

    stopTimer();
    pressCounter += 1;
    Serial.println("Hävisit pelin");  // If pressed button and generated number didn't match 
    gameIsOn = false;                 // Sets game off
    buttonPressed = false;            // Initializes value

    Serial.print("Pelin arpomat numerot:\t\t");   // Print list of generated random numbers on serial monitor
    for (int i = 0; i< nextRandomNumber; i++) {
      Serial.print(randomNumbers[i]);
    }
    Serial.println(" ");
    Serial.print("Sinun painamat numerot:\t\t");  // Print list of player pressed button numbers on serial monitor
    for (int i = 0; i< pressCounter; i++) {
      Serial.print(userNumbers[i]);
    }
    Serial.println(" ");
    playMelody();                     // Play melody when game ends
    ledFlashSequence();               // Flash leds
    showResult(highScore);            // Show highScore on display
  }
}

void initializeGame() {
  initializeTimer();
  initializeLeds();
  initializeDisplay();

  // Initializes all variables to zero values. More comments in header file
  currentScore = 0;
  userInput = NULL;
  pressCounter = 0;
  buttonPressed = false;
  nextRandomNumber = 0;
  randomSeed(millis()); 

  buttonMillis = 0;                   // Variable to save millis() time when button is pressed
  lastButtonReading = 1;              // Variable to save the last reading from a button press (For debouncing)
  clearAllLeds();                     // Clear leds
  showResult(currentScore);           // Show 00 score on display
}

void startTheGame() {

  Serial.println("*****Game Started*****");
  initializeGame();                   // Initialize all modules and variables
  gameIsOn = true;                    // Set game state
  startTimer();                       // Start timer
}

int generateRandomNumber() {
  // Generates random number 0-3
  return random(0,4);
}

void startTimer() {

  TIMSK1 = 0x02;                      // Enable interrupts setup
}

void stopTimer() {
                      
  TIMSK1 = 0x00;                      // Disable interrupts setup
}
