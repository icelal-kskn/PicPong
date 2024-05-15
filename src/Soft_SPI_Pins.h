#ifndef SPI_PINS_H
#define	SPI_PINS_H
//------------------------------------------------------------------------------
#include <xc.h>
//------------------------------------------------------------------------------
#define SCLK       RC2         //Serial Clock
#define SDOUT      RC0         //Serial Data Out
#define SDIN       RC4         //Serial Data In
#define CS0        RC1         //Chip 1 Select
#define CS1        RC3         //Chip 2 Select
//---------------------------DIRECTION------------------------------------------
#define SCLK_dir   TRISC2
#define SDOUT_dir  TRISC0
#define SDIN_dir   TRISC4
#define CS0_dir    TRISC1
#define CS1_dir    TRISC3
//------------------------------------------------------------------------------
#endif