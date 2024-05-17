/*
 * File:   Soft_SPI_Pins.c
 * Author: msert
 *
 * Created on 12 May?s 2024 Pazar, 14:56
 */


#include <xc.h>
#include "Soft_SPI.h"

void SPI_init(void) {
    SCLK_dir = 0;
    SDOUT_dir = 0;
    SDIN_dir = 1;
    CS0_dir = 0;
    CS1_dir = 0;
}
//--------------------------TX: transmit data-----------------------------------

void SPI_write(char send) {
    for (int Tx = 0; Tx < 8; Tx++) {
        SCLK = 0;
        SDOUT = ((send << Tx) & 0x80) ? 1 : 0; //MSB first.
        SCLK = 1;
    }
}
//--------------------------RX: recieve data------------------------------------

char SPI_read(void) {
    char data = 0;

    for (int Rx = 0; Rx < 8; Rx++) {
        SCLK = 0;
        data += (SDIN << (7 - Rx)); //MSB first.
        SCLK = 1;
    }

    return data;
}
