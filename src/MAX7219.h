#ifndef MAX7219_H
#define	MAX7219_H
//------------------------Dot Matrix LED  Driver--------------------------------
#include "Soft_SPI.h"
#include "MAX7219_Prototypes.h"
//------------------------------------------------------------------------------
void MAX7219_init(char noChips);
//------------------------------------------------------------------------------
void MAX7219_config(char chip);
//------------------------------------------------------------------------------
void MAX7219_write(char regName,char data);
//------------------------------------------------------------------------------
void MAX7219_NoOperation();
//------------------------------------------------------------------------------
void MAX7219_draw_ball(char* ball);

void initPlayersPad();
void updatePlayerPosition(int player, int direction);
#endif	