#include "melody.h"


void playMelody(void) {

  int startMelody[] = {NOTE_D4, NOTE_F4, NOTE_A4, NOTE_D5, NOTE_F5, NOTE_A5, NOTE_D6, NOTE_F6,
                      NOTE_G6, NOTE_E6, NOTE_CS6, NOTE_AS5, NOTE_G5, NOTE_AS5, NOTE_CS6, NOTE_E6,
                      NOTE_A6, NOTE_F6, NOTE_D6, NOTE_A5, NOTE_F5, NOTE_A5, NOTE_D6, NOTE_F6, 
                      NOTE_AS6, NOTE_G6, NOTE_E6, NOTE_CS6, NOTE_AS5, NOTE_CS6, NOTE_E6, NOTE_G6,
                      NOTE_A6, NOTE_F6, NOTE_D6, NOTE_A5, NOTE_F5, NOTE_A5, NOTE_D6, NOTE_F6,
                      NOTE_GS6, NOTE_F6, NOTE_D6, NOTE_B5, NOTE_GS5, NOTE_B5, NOTE_D6, NOTE_F6,
                      NOTE_A6, NOTE_E6, NOTE_CS6, NOTE_A5, NOTE_E5, NOTE_A5, NOTE_CS6, NOTE_E6
                      };
  int speakerPin = 6;
  
  // Define the note duration (in milliseconds)
  int noteDuration = 75;
  // Iterate over the array of notes
  for (int i = 0; i < 56; i++) {
    // Play the note on the piezo speaker
    tone(speakerPin, startMelody[i], noteDuration);

    delay(noteDuration);  // Note duration 
    delay(5);             // Stability playing notes
  }
  
  tone(speakerPin, NOTE_D6, 500);
  delay(1000);
}

