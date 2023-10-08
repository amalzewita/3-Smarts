#include "keypad.h"
#include "tm4c123gh6pm.h"
#include "delay.h"

static const uint8 mapping[4][4] = { {1, 2, 3, '+'},
{4, 5, 6, '-'},
{7, 8, 9, '/'},
{'*', 0, '#', '='} };

void KEYPAD_init(){
  SYSCTL_RCGCGPIO_R |= 0x14;            //enable clc for port C & E
  while ((SYSCTL_RCGCGPIO_R&0x14)==0);  //wait for clock to be enabled
  GPIO_PORTC_CR_R  |= 0xF0;             //allow changes to all the bits in port C
  GPIO_PORTE_CR_R  |= 0x0F;             //allow changes to all the bits in port E
  GPIO_PORTC_DIR_R |= 0xF0;             //set directions cols are o/ps
  GPIO_PORTE_DIR_R |= 0x00;             //set directions raws are i/ps
  GPIO_PORTE_PDR_R |= 0x0F;             //pull down resistor on Raws
  GPIO_PORTC_DEN_R |= 0xF0;             //digital enable pins in port C
  GPIO_PORTE_DEN_R |= 0x0F;             //digital enable pins in port E
  
}
uint8 KEYPAD_getPressedKey(void)
{
  int break1=0;
  while(break1==0)
  {
    if(DIO_ReadPin(PORTB,2)==0)
    {
      break1 = 1;
    }
    uint8 i,j;
    for(i = 0; i < 4; i++)                        //columns traverse
    {
      GPIO_PORTC_DATA_R = (1<<(i+4));
      delay_us(2);
      for(j = 0; j < 4; j++)                     //raws traverse
      {
        if((GPIO_PORTE_DATA_R & 0x0F) & (1<<(j)))
        {
          return mapping[j][i];
        }
      }
    }
  }
}
  char KEYPAD_getPressedKey2(void){

  int break1=0;
  while(break1==0)
  {
    if(DIO_ReadPin(PORTB,2)==0)
    {
      break1 = 1;
    }
    
    uint8 i,j;
    for(i = 0; i < 4; i++)                        //columns traverse
    {
      GPIO_PORTC_DATA_R = (1<<(i+4));
      delay_us(2);
      for(j = 0; j < 4; j++)                     //raws traverse
      {
        if((GPIO_PORTE_DATA_R & 0x0F) & (1<<(j)))
        {
          return mapping[j][i];
        }
      }
    }
  }

  }
