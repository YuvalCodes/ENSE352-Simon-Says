#include "stm32F103RB.h"
#include "main.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#define NUMBER_OF_LEDS 4

void delay();
void StartSeq(void);
void failSeq(void);
void WonSeq();
bool buttonPress();
int randomNumberTo4();
int seq[10];
bool rounds(int round);
void wait_for_user_input();
void wait_for_user_input_won();
void wait_for_user_input_fail();

int main(void)
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 {
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN |RCC_APB2ENR_IOPCEN;
			 
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	
	GPIOA->CRL &= ~((0xF << (4 * 0)) | (0xF << (4 * 1)) | (0xF << (4 * 4))); // Clear Pin A4/A1/A0
	GPIOA->CRL |= (0x3 << (4 * 0)) | (0x3 << (4 * 1)) | (0x3 << (4 * 4));  // Set Oub A4/A1/A0
	
	GPIOB->CRL &= ~((0xF << (4 * 0)) | (0xF << (4 * 4)) | (0xF << (4 * 6)));  // Clear Pin B6/B4/B0
	GPIOB->CRL |= (0x3 << (4 * 0)) | (0x4 << (4 * 4)) | (0x4 << (4 * 6)); // Set Pin B6/B4/B0
	
	GPIOB->CRH &= ~((0xF << (4 * 0)) | (0xF << (4 * 1)));  // Clear Pin B9/B8
	GPIOB->CRH |= (0x4 << (4 * 0)) | (0x4 << (4 * 1)); // Set Pin B9/B8


			 

			 
			 
while (1){

for(int i = 0; i < 10; i++){
seq[i] = randomNumberTo4(); // generate sequence for each new game
}


wait_for_user_input(); // waiting for user to start game

delay();
delay();

while(rnd != 11){ // while round is not 11 as we need round to equal 10 to display 10 rounds
	if(rounds(rnd)){ // calling rounds function with rnd as variable to display the right amount of LED's
	rnd++; // if the win the round this loop will keep going and increase the rnd till we reach 11
	delay();
	delay();
	} else { // break if they fail a round or rnd == 11
	break;
	}
} 

if(rnd == 11) { // check if rnd is equal to 11 , means they won and play Won Sequence
rnd--; // decrease rnd as we are displaying the round that they made it to with this variable and want to show 10
	for (int i = 0; i <= 3; i++){ // Bleep lights 4 times
		GPIOA->ODR |= (1 << 0) | (1 << 1) | ( 1 << 4);
		GPIOB-> ODR |= (1 << 0);
		delay();
		GPIOA-> ODR &= ~((1 << 0) | (1 << 1) | (1 << 4));
		GPIOB -> ODR &= ~(1 << 0);
		delay();
	}
wait_for_user_input_won(); // call function to display Won Seq() until they click a button
rnd = 1; // reset rnd to 1
delay();
delay();
delay();
}else { // if they fail to play fail Seq
for (int j = 0; j < 4; j++){ // POlice Siren code lights
for (int i= 0; i <= 3; i++)
	{
		if (i == 0) {
		GPIOA ->ODR |= (1 << 0);
		GPIOA -> ODR |= (1 << 1);
		}else if (i == 1) {
		GPIOA -> ODR |= (1 << 4);
		GPIOB -> ODR |= (1 << 0);
		} else if ( i == 2) {
		GPIOA ->ODR |= (1 << 0);
		GPIOA -> ODR |= (1 << 1);
		}else if (i == 3) {
		GPIOA -> ODR |= (1 << 4);
		GPIOB -> ODR |= (1 << 0);
		}
		startdelay();
		delay();
	GPIOA->ODR &= ~((1 << 0) | (1 << 1) | (1 << 4));
	GPIOB->ODR &= ~(1 << 0);
		}
	delay();
	}
rnd--; // decrease round as again if they fail on round 8, it should show round 7 as the accomplished level
wait_for_user_input_fail(); // display the round and wait for user input to restart game
rnd = 1; // reset to rnd 1
delay();
delay();
delay();
}
}
}	 
	
void StartSeq(void){
	for (int i= 0; i < 4; i++)
	{
		if (i == 0) {
		GPIOA ->ODR |= (1 << 0);
		}else if (i == 1) {
		GPIOA -> ODR |= (1 << 1);
		} else if ( i == 2) {
		GPIOA -> ODR |= (1 << 4);
		}else if (i == 3) {
		GPIOB -> ODR |= (1 << 0);
		}
		startdelay();
	GPIOA->ODR &= ~((1 << 0) | (1 << 1) | (1 << 4));
	GPIOB->ODR &= ~(1 << 0);
		}
	for (int i= 3; i >= 0; i--)
	{
		if(buttonPress()){
		return;
		}
		if (i == 0) {
		GPIOA ->ODR |= (1 << 0);
		}else if (i == 1) {
		GPIOA -> ODR |= (1 << 1);
		} else if ( i == 2) {
		GPIOA -> ODR |= (1 << 4);
		}else if (i == 3) {
		GPIOB -> ODR |= (1 << 0);
		}
		startdelay();
		GPIOA-> ODR &= ~((1 << 0) | (1 << 1) | (1 << 4));
		GPIOB -> ODR &= ~(1 << 0);
		}
}


void failSeq (void)
{
 if (( rnd >> 3) & 1) { 
        GPIOA->ODR |= (1 << 0);   
    } else {
        GPIOA->ODR &= ~(1 << 0);  
    }
    
    if (( rnd >> 2) & 1) {  
        GPIOA->ODR |= (1 << 1);   
    } else {
        GPIOA->ODR &= ~(1 << 1);  
    }
    
    if (( rnd >> 1) & 1) {  
        GPIOA->ODR |= (1 << 4);   
    } else {
        GPIOA->ODR &= ~(1 << 4);  
    }

    if ( rnd & 1) {  
        GPIOB->ODR |= (1 << 0);  
    } else {
        GPIOB->ODR &= ~(1 << 0); 
    }
}

void WonSeq (void) {
 if (( rnd >> 3) & 1) { 
        GPIOA->ODR |= (1 << 0);   
    } else {
        GPIOA->ODR &= ~(1 << 0);  
    }
    
    if ((rnd >> 2) & 1) {  
        GPIOA->ODR |= (1 << 1);   
    } else {
        GPIOA->ODR &= ~(1 << 1);  
    }
    
    if (( rnd >> 1) & 1) {  
        GPIOA->ODR |= (1 << 4);   
    } else {
        GPIOA->ODR &= ~(1 << 4);  
    }

    if ( rnd & 1) {  
        GPIOB->ODR |= (1 << 0);  
    } else {
        GPIOB->ODR &= ~(1 << 0); 
    }
}


bool buttonPress(void){
        if(!(GPIOB->IDR & (1<<4))) return true; // button black
        else if(!(GPIOB->IDR & (1<<6))) return true; // button red
        else if(!(GPIOB->IDR & (1<<8))) return true;// button green
        else if(!(GPIOB->IDR & (1<<9))) return true;// butten blue
				else {return false;}
}

int whichButton(void){
	if(!(GPIOB->IDR & (1<<4))) return 1; // button black
  else if(!(GPIOB->IDR & (1<<6))) return 2; // button red
  else if(!(GPIOB->IDR & (1<<8))) return 3;// button green
  else if(!(GPIOB->IDR & (1<<9))) return 4;// butten blue
	else return -1;
}
int randomNumberTo4()
{
    int limit;
    int r;

    limit = RAND_MAX - (RAND_MAX % NUMBER_OF_LEDS);

    while((r = rand()) >= limit);
 
    return r % NUMBER_OF_LEDS;
}



bool rounds(int round) {
    int userInput[round];
    const int MAX_COUNT = 8000000; 
    int counter = MAX_COUNT;
    int inputsReceived = 0;


    for (int i = 0; i < round; i++) {
        int light = seq[i];
        switch (light) {
            case 0: GPIOA->ODR |= (1 << 0); break;
            case 1: GPIOA->ODR |= (1 << 1); break;
            case 2: GPIOA->ODR |= (1 << 4); break;
            case 3: GPIOB->ODR |= (1 << 0); break;
        }
        delay();
        GPIOA->ODR &= ~((1 << 0) | (1 << 1) | (1 << 4));
        GPIOB->ODR &= ~(1 << 0);
        delay();
    }


    while (counter > 0) {
        int whichbut = -1;

  
        if (inputsReceived < round) {
            whichbut = whichButton();

            if (whichbut != -1) {
                userInput[inputsReceived] = whichbut - 1;

                
                switch (userInput[inputsReceived]) {
                    case 0: GPIOA->ODR |= (1 << 0); break;
                    case 1: GPIOA->ODR |= (1 << 1); break;
                    case 2: GPIOA->ODR |= (1 << 4); break;
                    case 3: GPIOB->ODR |= (1 << 0); break;
                }
                delay();
                GPIOA->ODR &= ~((1 << 0) | (1 << 1) | (1 << 4));
                GPIOB->ODR &= ~(1 << 0);

                inputsReceived++;
            }
        }

  
        if (inputsReceived == round) {
            break;
        }

        counter--;
    }


    if (counter == 0) {
        return false;
    }

   
    for (int i = 0; i < round; i++) {
        if (userInput[i] != seq[i]) {
            return false;
        }
    }

    return true; 
}

void wait_for_user_input() {
while (1) {
	StartSeq();
	 
	 if (!(GPIOB->IDR & (1 << 4)) ||  // Black Button
            !(GPIOB->IDR & (1 << 6)) ||  // Red Button
            !(GPIOB->IDR & (1 << 8)) ||  // Green Button
            !(GPIOB->IDR & (1 << 9))) {  // Blue Button
            break;
			}
}

}

void wait_for_user_input_won() {
while (1) {
	WonSeq();
	 
	 if (!(GPIOB->IDR & (1 << 4)) ||  // Black Button
            !(GPIOB->IDR & (1 << 6)) ||  // Red Button
            !(GPIOB->IDR & (1 << 8)) ||  // Green Button
            !(GPIOB->IDR & (1 << 9))) {  // Blue Button
            break;
			}
}

}

void wait_for_user_input_fail() {
while (1) {
	failSeq();
	 
	 if (!(GPIOB->IDR & (1 << 4)) ||  // Black Button
            !(GPIOB->IDR & (1 << 6)) ||  // Red Button
            !(GPIOB->IDR & (1 << 8)) ||  // Green Button
            !(GPIOB->IDR & (1 << 9))) {  // Blue Button
            break;
			}
}

}

