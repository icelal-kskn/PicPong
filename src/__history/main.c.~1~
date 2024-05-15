#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//------------------------------------------------------------------------------
#include "MAX7219.h"
//------------------------------------------------------------------------------
#define PLAYER_BLOCK_LEN 8
#define _XTAL_FREQ 800000000

#define Player1_up_pin RB0
#define Player1_down_pin RB1
#define Player2_up_pin RB2
#define Player2_down_pin RB3

#define No_Light 0b00000000
#define Row1 0b00000001
#define Row2 0b00000010
#define Row3 0b00000100
#define Row4 0b00001000
#define Row5 0b00010000
#define Row6 0b00100000
#define Row7 0b01000000
#define Row0 0b10000000


//columlar sa?dan sola 0 1 2 3 4 5 6 7  diye gidiyor
//rowlar yukar?dan a?a??ya Row8 1 2 3 4 5 6 7 diye gidiyor
bool button0pressed = false;
bool button1pressed = false;
bool button2pressed = false;
bool button3pressed = false;

char p1State = Row2 | Row3 | Row4 | Row5 ;
char p2State = Row2 | Row3 | Row4 | Row5 ; 

bool readButton0State() {
    // Dü?me pinini oku
    return (PORTB & (1 << Player1_up_pin)) == 0; // Dü?me bas?ld???nda LOW olacak ?ekilde ba?l? varsay?yoruz
}
bool readButton1State() {
    // Dü?me pinini oku
    return (PORTB & (1 << Player1_down_pin)) == 0; // Dü?me bas?ld???nda LOW olacak ?ekilde ba?l? varsay?yoruz
}
bool readButton2State() {
    // Dü?me pinini oku
    return (PORTB & (1 << Player2_up_pin)) == 0; // Dü?me bas?ld???nda LOW olacak ?ekilde ba?l? varsay?yoruz
}
bool readButton3State() {
    // Dü?me pinini oku
    return (PORTB & (1 << Player2_down_pin)) == 0; // Dü?me bas?ld???nda LOW olacak ?ekilde ba?l? varsay?yoruz
}


int main(int argc, char** argv) 
{
  MAX7219_init(1);  //Pass number of Chips as argument
  initPlayersPad();

  while(1)
    {
      //if !Finish Game Finished method
      
      button0pressed = readButton0State();
      button1pressed = readButton1State();
      button2pressed = readButton2State();
      button3pressed = readButton3State();

      // Oyuncu 1
      if (button0pressed && !button1pressed) {
          updatePlayerPosition(1, 1); // 1 yukar?
      } else if (!button0pressed && button1pressed) {
          updatePlayerPosition(1, 0); // 1 a?a??
      }

      // Oyuncu 2
      if (button2pressed && !button3pressed) {
          updatePlayerPosition(2, 1); // 2 yukar?
      } else if (!button2pressed && button3pressed) {
          updatePlayerPosition(2, 0); // 2 a?a??
      }
    }
    
  
  return (EXIT_SUCCESS);
}

void initPlayersPad(){
    MAX7219_write(8 , p1State );
    MAX7219_write(1 , p2State );
}

char buttonGoUp(char currentState){
    return currentState << 1;
}

char buttonGoDown(char currentState){
    return currentState >> 1;
}

void updatePlayerPosition(int player, int direction) {
    if (player == 1) {
        if (direction == 1) { // Yukar?
            p1State = buttonGoUp(p1State);
            MAX7219_write(8, p1State);
        } else { // A?a??
            p1State = buttonGoDown(p1State);
            MAX7219_write(8, p1State);
        }
    } else {
        if (direction == 1) { // Yukar?
            p2State = buttonGoUp(p2State);
            MAX7219_write(1, p2State);
        } else { // A?a??
            p2State = buttonGoDown(p2State);
            MAX7219_write(1, p2State);
        }
    }
}







