#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//------------------------------------------------------------------------------
#include "MAX7219.h"
//------------------------------------------------------------------------------
#define PLAYER_BLOCK_LEN 8
#define _XTAL_FREQ 800000000

#define DEBOUNCE_DELAY 10

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

//columlar sagdan sola 0 1 2 3 4 5 6 7  diye gidiyor
//rowlar yukaridan asag?ya Row 1 2 3 4 5 6 7 0 diye gidiyor
bool button0pressed = false;
bool button1pressed = false;
bool button2pressed = false;
bool button3pressed = false;

char p1State = Row2 | Row3 | Row4 | Row5;
char p2State = Row2 | Row3 | Row4 | Row5;

int ballDirX = 1;
int ballDirY = 1;
int ballX = 4;
char ballYState = Row4;

bool readButton0State() {
    if (RB0 == 0) { // Buton bas?ld?ysa
        return true;
    }
    return false;
}

bool readButton1State() {
    if (RB1 == 0) { // Buton bas?ld?ysa
        return true;
    }
    return false;
}

bool readButton2State() {
    if (RB2 == 0) { // Buton bas?ld?ysa
        return true;
    }
    return false;
}

bool readButton3State() {
    if (RB3 == 0) { // Buton bas?ld?ysa
        return true;
    }
    return false;
}

void initPorts() {
    TRISB = 0x0F; // init input
    TRISC = 0x00; //init output
    MAX7219_init(1);
}

void initGame() {
    ballX = 4;
    ballYState = Row4;
    MAX7219_write(8, p1State);
    MAX7219_write(1, p2State);
    MAX7219_write(ballX, ballYState);
}

char buttonGoUp(char currentState) {
    if (currentState & (Row4 | Row5 | Row6 | Row7)) {
        return currentState;
    }
    return currentState << 1;
}

char buttonGoDown(char currentState) {
    if (currentState & (Row0 | Row1 | Row2 | Row3)) {
        return currentState;
    }
    return currentState >> 1;
}

void updatePlayerPosition(int player, int direction) {
    if (player == 1) {
        if (direction == 1) { // Yukari
            p1State = buttonGoUp(p1State);
            MAX7219_write(8, p1State);
        } else { // Asag?
            p1State = buttonGoDown(p1State);
            MAX7219_write(8, p1State);
        }
    } else {
        if (direction == 1) { // Yukari
            p2State = buttonGoUp(p2State);
            MAX7219_write(1, p2State);
        } else { // Asagi
            p2State = buttonGoDown(p2State);
            MAX7219_write(1, p2State);
        }
    }
}

void updateBallPosition() {
    //Topun column kordinatlar?
    if (ballX < 1 || ballX > 8) { // S?n?rlar
        ballDirX = -ballDirX;
    }
    ballX += ballDirX;

    if ((ballYState & Row0) || (ballYState & Row7)) { //s?n?rlar
        ballDirY = -ballDirY;
    }
    ballYState = (ballDirY == 1) ? ballYState << 1 : ballYState >> 1;

    MAX7219_write(ballX, ballYState);
}

int main(int argc, char** argv) {
    initPorts();
    initGame();

    while (1) {
        //if !Finish Game Finished method
        __delay_ms(10); // Topun h?z?n? ayarlamak için gecikme
        button0pressed = readButton0State();
        button1pressed = readButton1State();
        button2pressed = readButton2State();
        button3pressed = readButton3State();

        // Oyuncu 1
        if (button0pressed) {
            updatePlayerPosition(1, 1); // 1 yukari
        } else if (button1pressed) {
            updatePlayerPosition(1, 0); // 1 asagi
        }

        // Oyuncu 2
        if (button2pressed) {
            updatePlayerPosition(2, 1); // 2 yukari
        } else if (button3pressed) {
            updatePlayerPosition(2, 0); // 2 asagi
        }
        updateBallPosition();
    }

    return (EXIT_SUCCESS);
}
