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

#define STATE_5 0b01111000 
#define STATE_4 0b00111100
#define STATE_3 0b00011110
#define STATE_2 0b00001111
#define STATE_1 0b10000111
//Stateler do?ru :(

//(8,Row0), (7,Row0), (6,Row0), (5,Row0), (4,Row0), (3,Row0), (2,Row0), (1,Row0)
//(8,Row1), (7,Row1), (6,Row1), (5,Row1), (4,Row1), (3,Row1), (2,Row1), (1,Row1)
//(8,Row2), (7,Row2), (6,Row2), (5,Row2), (4,Row2), (3,Row2), (2,Row2), (1,Row2)
//(8,Row3), (7,Row3), (6,Row3), (5,Row3), (4,Row3), (3,Row3), (2,Row3), (1,Row3)
//(8,Row4), (7,Row4), (6,Row4), (5,Row4), (4,Row4), (3,Row4), (2,Row4), (1,Row4)
//(8,Row5), (7,Row5), (6,Row5), (5,Row5), (4,Row5), (3,Row5), (2,Row5), (1,Row5)
//(8,Row6), (7,Row6), (6,Row6), (5,Row6), (4,Row6), (3,Row6), (2,Row6), (1,Row6)
//(8,Row7), (7,Row7), (6,Row7), (5,Row7), (4,Row7), (3,Row7), (2,Row7), (1,Row7)

char p1State = STATE_3;
char p2State = STATE_3;

int ballDirX = -1;
int ballDirY = 1;
int ballX = 4;
char ballYState = Row4;

int isScore=0;

void initGame() {
    ballX = 4;
    ballYState = Row4;
    MAX7219_write(8, p1State);
    MAX7219_write(1, p2State);
    MAX7219_write(ballX, ballYState);
}


int readButton0() {
    return Player1_up_pin;
}
int readButton1() {
    return Player1_down_pin;
}
int readButton2() {
    return Player2_up_pin;
}
int readButton3() {
    return Player2_down_pin;
}

void buttonGoUp(int player) {
    if (player ==1){
        switch (p1State){
            case STATE_1:
                p1State=STATE_2;
                MAX7219_write(7, p1State); 
                break;
            case STATE_2:
                p1State=STATE_3;
                MAX7219_write(7, p1State);
                break;
            case STATE_3:
                p1State=STATE_4;
                MAX7219_write(7, p1State);                
                break;
            case STATE_4:
                p1State=STATE_5;
                MAX7219_write(7, p1State); 
                break;
            case STATE_5:
                p1State=STATE_5;
                MAX7219_write(7, p1State);
                break;
            default:
                p1State =STATE_3;
                MAX7219_write(7, p1State);
                break;
        }
    }
    else{
        switch (p2State){
            case STATE_1:
                p2State=STATE_2;
                MAX7219_write(2, p2State); 
                break;
            case STATE_2:
                p2State=STATE_3;
                MAX7219_write(2, p2State);
                break;
            case STATE_3:
                p2State=STATE_4;
                MAX7219_write(2, p2State);                
                break;
            case STATE_4:
                p2State=STATE_5;
                MAX7219_write(2, p2State); 
                break;
            case STATE_5:
                p2State=STATE_5;
                MAX7219_write(2, p2State);
                break;
            default:
                p2State = STATE_3;
                MAX7219_write(2, p2State);
                break;
        }
    }      
}

void buttonGoDown(int player) {
    if (player ==1){
        switch (p1State){
            case STATE_1:
                p1State=STATE_1;
                MAX7219_write(7, p1State); 
                break;
            case STATE_2:
                p1State=STATE_1;
                MAX7219_write(7, p1State);
                break;
            case STATE_3:
                p1State=STATE_2;
                MAX7219_write(7, p1State);                
                break;
            case STATE_4:
                p1State=STATE_3;
                MAX7219_write(7, p1State); 
                break;
            case STATE_5:
                p1State=STATE_4;
                MAX7219_write(7, p1State);
                break;
            default:
                p1State = STATE_3;
                MAX7219_write(7, p1State);
                break;
        }
    }
    else{
        switch (p2State){
            case STATE_1:
                p2State=STATE_1;
                MAX7219_write(2, p2State); 
                break;
            case STATE_2:
                p2State=STATE_1;
                MAX7219_write(2, p2State);
                break;
            case STATE_3:
                p2State=STATE_2;
                MAX7219_write(2, p2State);                
                break;
            case STATE_4:
                p2State=STATE_3;
                MAX7219_write(2, p2State); 
                break;
            case STATE_5:
                p2State=STATE_4;
                MAX7219_write(2, p2State);
                break;
            default:
                p2State = Row2 | Row3 | Row4 | Row5;
                MAX7219_write(2, p2State);
                break;
        }
    } 
}
void updateBallPosition() {
    int ballXprev= ballX;
    //Topun column kordinatlar?
    if (ballX ==  || ballX == 8) { // Sinirlar
        ballDirX = -ballDirX;
    }
    ballX += ballDirX;

    if ((ballYState & p1State)!= No_Light || (ballYState & p2State) != No_Light) { //pad kontrol
        ballDirY = -ballDirY;
    }
    ballYState = (ballDirY == 1) ? ballYState << 1 : ballYState >> 1;
    
    MAX7219_write(ballXprev, No_Light);
    MAX7219_write(ballX, ballYState);
}

void initGame() {
    ballX = 4;
    ballYState = Row4;
    MAX7219_write(7, p1State);
    MAX7219_write(2, p2State);
    MAX7219_write(ballX, ballYState);
}

int main(int argc, char** argv) {
    TRISB = 0x0F; // init input
    TRISC = 0; //init output
    //initGame();
    MAX7219_init(1);
    
    while(1){
        //update_ball_position
        //__delay_ms(10);
        if(readButton0() == 1){
            buttonGoUp(1);
        }
        if(readButton1() == 1){
            buttonGoDown(1);
        }
        if(readButton2() == 1){
            buttonGoUp(2);
        }
        if(readButton3() == 1){
            buttonGoDown(2);
        }
        
    }

    return (EXIT_SUCCESS);
}
