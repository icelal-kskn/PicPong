#ifndef MAX7219_PROTOTYPES_H
#define	MAX7219_PROTOTYPES_H
//------------------------------------------------------------------------------
#define NO_OP_REG           0x00     //Used for Max7219 Cascading purposes
#define DECODE_MODE_REG     0x09
#define INTESITY_REG        0x0A
#define SCAN_LIMIT_REG      0x0B
#define SHUTDOWN_REG        0x0C
#define DISPLAY_TEST_REG    0x0F
//------------------------------------------------------------------------------
#define DISABLE_DECODE      0x00
#define BRIGHTNESS          0x05     //Can be alterterd to suite requirement
#define SCAN_ALL_DIGITS     0x07   
#define SHUTDOWN_MODE       0x00
#define NORMAL_OPERATION    0x01
#define DISABLE_TEST        0x00   
//------------------------------------------------------------------------------
void MAX7219_init(char noChips);
void MAX7219_config(char chip);
void MAX7219_write(char regName, char data);
void MAX7219_displayText(char* text);
void MAX7219_NoOperation(void);
//------------------------------------------------------------------------------
#endif