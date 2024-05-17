/*
 * File:   MAX7219.c
 * Author: msert
 *
 * Created on 12 May?s 2024 Pazar, 14:58
 */


#include <xc.h>
#include "MAX7219.h"

void MAX7219_init(char noChips) {
    SPI_init();
    while (noChips)
        MAX7219_config(--noChips);
}
//------------------------------------------------------------------------------

void MAX7219_config(char chip) {
    MAX7219_write(DECODE_MODE_REG, DISABLE_DECODE);
    MAX7219_write(INTESITY_REG, BRIGHTNESS);
    MAX7219_write(SCAN_LIMIT_REG, SCAN_ALL_DIGITS);
    MAX7219_write(SHUTDOWN_REG, NORMAL_OPERATION);
    MAX7219_write(DISPLAY_TEST_REG, DISABLE_TEST);
}
//------------------------------------------------------------------------------

void MAX7219_write(char regName, char data) {
    CS0 = 0;

    SPI_write(regName);
    SPI_write(data); //Used for daisy chained (Cascaded) arrangements

    CS0 = 1;
}
//------------------------------------------------------------------------------

void MAX7219_displayText(char* text) {
    for (int col = 1; col < 9; col++) {
        MAX7219_write((char) col, text[col]);
    }
}
//-----------Passes the data to the adjacent MAX7219 in the Daisy Chain---------

void MAX7219_NoOperation() {
    SPI_write(NO_OP_REG);
    SPI_write(0x00); //Don't care (Can be any arbitrary value)
}
