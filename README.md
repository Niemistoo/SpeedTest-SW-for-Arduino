# Speedtest SW for Arduino
![Gameboard](/images/Gameboard.jpg)

## Project Info

This program is for micro controllers with ATmega328P chip. Project is tested and built with Arduino Uno R3 board. 

The project is made as a team school project. All the code is made by Github/Niemistoo except code related to button debounce is made by Github/Haarmes. Original name for project was **SpedenSpelit**, that is related to Finnish tv-show which brought to fame the original version of this game.

## How to deploy the code

1. Build the hardware.
2. Download the code. Use Arduino IDE to upload the code for micro controller. Keep all the files in same directory.
3. Have fun

![Speedtest_Wiring](/images/Speedtest_wiring_tinkercad.png)


## How does it work? What to expect?

1. Power on
    - melody plays
    - display shows "00"
    - game is on the idle mode and leds are flashing
2. Start pressed
    - leds flashes 3 times as "turn on, turn off"
    - score is initialized to 00 on display
    - game starts to generate random numbers, that present which led is turned on
    - user is expected to press the button, which led is turned on
    - there is no time limit to press button, but order must be same as randomly generated
    - if correct button was pressed -> score increases +1 and is shown on display
    - speed increases 2% after every generated number
    - max generated numbers is 99
3. Wrong button pressed
    - check your score 
    - melody plays.. again
    - leds runs the same flash sequence as when the game was started.
    - scoreboard shows the highest score made after reset of the game.
    - game is on the idle mode
    - options -> play again(press start)

    ![Speedtest_Prototype](/images/Speedtest_prototype.jpg)

## Part list

- Arduino Uno R3
- 4pcs led
- 4pcs 470ohm resistor (for leds)
- 5pcs push buttons
- 2pcs 7-segment-display (common anode)
- 2pcs 470ohm resistor (for displays. I recommend to use resistor for each segment for avoid light dimmening when multiple leds is on)
- 2pcs MC74HC595 8-bit shift register
- 1pcs piezo speaker
- power source (USB-powered Arduino)
- bread boards
- wiring