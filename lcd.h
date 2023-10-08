
#ifndef LCD_H_
#define LCD_H_

#include "tm4c123gh6pm.h"
#include "types.h"

#define LCD_DATA        GPIO_PORTB_DATA_R   /* Define "LCD" as a symbolic name for GPIOB */
#define LCD_DIR         GPIO_PORTB_DIR_R
#define LCD_DEN         GPIO_PORTB_DEN_R 

#define RS 0x1 /* PORTB BIT0 mask */
#define RW 0x40 /* PORTB BIT6 mask */
#define EN 0x2 /* PORTB BIT1 mask */
#define HIGH 1
#define LOW 0

/*define useful symbolic names for LCD commands */
#define clear_display     0x01
#define returnHome        0x02
#define moveCursorRight   0x06
#define moveCursorLeft    0x08
#define shiftDisplayRight 0x1C
#define shiftDisplayLeft  0x18
#define cursorBlink       0x0F
#define cursorOff         0x0C
#define cursorOn          0x0E
#define Function_set_4bit 0x28
#define Function_set_8bit 0x38
#define Entry_mode        0x06
#define Function_8_bit    0x32
#define Set5x7FontSize    0x20
#define FirstRow          0x80

void LCD_init(void);  /* LCD initialization function */
void LCD_Cmd(unsigned char command); /*Used to send commands to LCD */
void LCD_Write_Char(unsigned char data); /* Writes ASCII character */
void LCD_Write_Nibble(unsigned char data, unsigned char control); /* Writes 4-bits */
void LCD_String (char *str);	/* Send string to LCD function */
void LCD_moveCursor(uint8 row,uint8 col);
void LCD_displayStringRowColumn(uint8 row,uint8 col, char *Str);
void LCD_intgerToString(int data);
void LCD_floatToString(double data);
void LCD_clearScreen(void);
int intToStr(int x, char str[], int d);
char * ftoa(double f, char * buf, int precision);
#endif /* LCD_H_ */
