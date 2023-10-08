#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "DIO.h"
#include "types.h"
#include "tm4c123gh6pm.h"

#define KEYPAD_NUM_COLS                   4
#define KEYPAD_NUM_ROWS                   4

void KEYPAD_init(void);
uint8 KEYPAD_getPressedKey(void);
char KEYPAD_getPressedKey2(void);


#endif