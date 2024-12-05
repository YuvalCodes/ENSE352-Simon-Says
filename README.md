Simon Says Game
By: Yuval Glozman
Class: ENSE352

Project Description: 

The Project was made for my Computer Systems Architecture Lab Final (ENSE352) and was based off the Simon Says game built by Hasbro

The project utilized the follow componenets

- STM32F103RB
- Breadboard
- Wires
- 10k Ohm Bus resistor
- 270 Ohm Resistors
- 4 LED's
- 4 Buttons

The code was built and compiled using C in Keil Vision.

The Project had these requirments

- When starting the game initiate a classic Cylon Eye Scanner or Knight Rider light sequence. Keep
this sequence until a user presses a button. This will initiate the first round of gameplay.

- Begin the game with one LED for round one. The user will mimic this light by pressing the
appropriate button. When the user presses the button, light the corresponding LED. The player
only has a limited amount of time to press the button. If the player is successful then move on to
round two and add a LED to the sequence. This will continue until round 10.

- 3 Game End
    The game ends if one of two ways:
        1. Failure Sequence.
        2. Game Won

- 3.1 Failure Sequence
    A failure can happen in one of two ways:
        • The player gets the sequence wrong.
        • A button is not pressed in time during the repeat sequence. How long? That is up to you as the game designer.

The failure sequence is up to you as the game designer. Create some LED sequence that indicates
failure by blinking this failure 4 times. Then the level achieved will be indicated by lighting the 4
bit binary pattern on the LED’s. The LED’s will remain in this pattern until the player presses any
button and a new game will resume.

- 3.2 Game Won!!
If the player completes 10 rounds successfully then the Game Won sequence will run. This will
be all 4 LED’s blinking on and off together 4 times. Then the level achieved will be indicated by
lighting the 4 bit binary pattern on the LED’s. The LED’s will remain in this pattern until the
player presses any button and a new game will resume.


How to Play the game

Step 1. Install the main.c, main.h, and the stm32F103RB.h file

Step 2. You can now initiate the game and once started you will be greeted with the Knight Rider Sequence, a press of any button will begin the game.

Once playing you now must complete 10 rounds successfully to get Win, by failing to return the correct sequence or failing to do it within the given time limit will result in the fail sequence and losing the game

Win Sequence
- Once completing all 10 rounds the Win Sequence will intiate
- All 4 lights will flash on and off four times before displaying the round you achieved to, in this case it will always be 10 displaying 1010.
- A press of any button after the round achieved is displayed will reset the game and take you back to the Knight Rider Sequence where you are able to start a new game.

Fail Sequence
- Failing at any round is possible either by returning the wrong sequence or running out of the alloted time
- This will cause the fail sequence to intiate which will make a police siren pattern on the LED's, the first 2 LED's flashing, and then the last 2 LED's. This will repeat 4 times.
- Afterwards the round you achieved will display, if you achieved round 4, 0100 will display on the LED's.
- Finally a press of any button will take you back to the Knight Rider Sequence where you can start a new game.