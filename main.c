#include "tm4c123gh6pm.h"
#include "math.h"
#include <string.h>

#include <DLib_Product_string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/timer.h"
#include "DIO.h"
#include "tm4c123gh6pm.h"
#include "keypad.h"
#include "bitwise_operation.h"
#include "lcd.h"
#include "delay.h"
#define UNLOCK 	0x4C4F434B

//timer on timer0
//stopwatch on timer1

/*-------------------Timer Functions------------------*/
void timer_start(void);
void timer_enable(void);
void timer_handler(void);
void timer_counter(int *y, int* z);
int timer_sec=0;
int* pointer_sec = &timer_sec;
int timer_min=0;
int* pointer_min = &timer_min;
int timerstatus1=0;
int* timer_status=&timerstatus1;
void timer_end(void);
/*-----------------Stopwatch Functions------------------*/
void stopwatch_start(void);
void stopwatch_handler(void);
void stopwatch_counter(int *y, int* z);
int stopwatch_sec=0;
int* pointer_stopwatch_sec = &stopwatch_sec;
int stopwatch_min=0;
int* pointer_stopwatch_min = &stopwatch_min;
void stopwatch_pause(void);
void stopwatch_resume(void);
void stopwatch_reset_handler(void);
void stopwatch_reset(int *y, int* z);
void stopwatch_end(void);
/*--------------Calculator Functions-----------------*/
void calculator_start(void);
float calc_num1=0;
float* calc_num1_pointer= &calc_num1;
float calc_num2=0;
float* calc_num2_pointer= &calc_num2;
void calculator_end(void);
/*---------------------------------------------------*/
void gpio_enable(void);
void button_int(void);
void select_mode(void);


int main()
{
  IntPrioritySet(INT_GPIOB_TM4C123,0x00);
  IntPrioritySet(INT_GPIOD_TM4C123,0xE0);  
  IntPrioritySet(INT_GPIOA_TM4C123,0xE0);
  IntPrioritySet(INT_GPIOF_TM4C123,0E4);
  /*-----------------initialize peripherals-----------------*/
  KEYPAD_init();
  LCD_init();
  LCD_Cmd(clear_display);
  /*----------------------initialize clocks---------------------*/
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0)){}
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER1)){}
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)){}
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA)){}
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD)){}
  
  /* button configuration of stopwatch pause on port F */
  GPIO_PORTF_LOCK_R = UNLOCK;                                                                 //unlock potrt f
  GPIOUnlockPin(GPIO_PORTF_BASE, GPIO_PIN_4);         
  GPIOPinTypeGPIOInput( GPIO_PORTF_BASE ,  GPIO_PIN_4);                                     //set pin to input
  GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4,GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
  GPIOIntEnable(GPIO_PORTF_BASE , GPIO_INT_PIN_4);
  GPIOIntRegister(GPIO_PORTF_BASE ,stopwatch_pause);                                       //register interrupt
  GPIOIntEnable(GPIO_PORTF_BASE , GPIO_INT_PIN_4);                                        //enable interrupt
  GPIOIntTypeSet(GPIO_PORTF_BASE,GPIO_PIN_4,GPIO_LOW_LEVEL); 
  
  /* button configuration of stopwatch resume on Port A */
  GPIO_PORTA_LOCK_R = UNLOCK;                                                          //unlock potrt A
  GPIOUnlockPin(GPIO_PORTA_BASE, GPIO_PIN_7);         
  GPIOPinTypeGPIOInput( GPIO_PORTA_BASE ,  GPIO_PIN_7);                                       //set pin to input
  GPIOPadConfigSet(GPIO_PORTA_BASE, GPIO_PIN_7,GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
  GPIOIntDisable(GPIO_PORTA_BASE , GPIO_INT_PIN_7);
  GPIOIntRegister(GPIO_PORTA_BASE ,stopwatch_resume);              //register interrupt
  GPIOIntEnable(GPIO_PORTA_BASE , GPIO_INT_PIN_7);      //enable interrupt
  GPIOIntTypeSet(GPIO_PORTA_BASE,GPIO_PIN_7,GPIO_LOW_LEVEL); 
  /* button configuration of stopwatch reset on Port D*/
  GPIO_PORTA_LOCK_R = UNLOCK;                                                          //unlock potrt D
  GPIOUnlockPin(GPIO_PORTD_BASE, GPIO_PIN_7);         
  GPIOPinTypeGPIOInput( GPIO_PORTD_BASE ,  GPIO_PIN_7);                                       //set pin to input
  GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_7,GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
  GPIOIntDisable(GPIO_PORTD_BASE , GPIO_INT_PIN_7);
  GPIOIntRegister(GPIO_PORTD_BASE ,stopwatch_reset_handler);              //register interrupt
  GPIOIntEnable(GPIO_PORTD_BASE , GPIO_INT_PIN_7);      //enable interrupt
  GPIOIntTypeSet(GPIO_PORTD_BASE,GPIO_PIN_7,GPIO_LOW_LEVEL); 
  /* button configuration for select mode on Port B */
  GPIO_PORTA_LOCK_R = UNLOCK;                                                          //unlock potrt D
  GPIOUnlockPin(GPIO_PORTB_BASE, GPIO_PIN_2);         
  GPIOPinTypeGPIOInput( GPIO_PORTB_BASE ,  GPIO_PIN_2);
  GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_2,GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
  GPIOIntEnable(GPIO_PORTB_BASE , GPIO_INT_PIN_2);
  GPIOIntRegister(GPIO_PORTB_BASE ,select_mode);     //register interrupt
  GPIOIntEnable(GPIO_PORTB_BASE , GPIO_INT_PIN_2);      //enable interrupt
  GPIOIntTypeSet(GPIO_PORTB_BASE,GPIO_PIN_2,GPIO_LOW_LEVEL); 
  
  /*----------------select mode----------------------------*/
  IntPrioritySet(INT_GPIOB_TM4C123,0x00);
  IntPrioritySet(INT_GPIOD_TM4C123,0xE0);  
  IntPrioritySet(INT_GPIOA_TM4C123,0xE0);
  IntPrioritySet(INT_GPIOF_TM4C123,0xE0);
  select_mode();
  
  while(1)
   {
    if( *timer_status==1 & KEYPAD_getPressedKey2()=='=' ){
    timer_enable();
    *timer_status=0;
  
}
  }
  
}

void select_mode(void){
  stopwatch_end();
  timer_end();
  LCD_moveCursor(0,0);
  LCD_String("select mode");
  int exit=0;
  while(exit==0){
  char mode;
  mode = KEYPAD_getPressedKey2();
  delay_ms(400);
    switch (mode){
  case '+':
    calculator_start();
    exit=1;
    break;
  case '-':
    timer_start();
    exit=1;
    break;
  case '/':
    stopwatch_start();
    exit=1;
    break;
    }
  }
  LCD_Cmd(cursorOff);
}
void calculator_start(){
  LCD_clearScreen();
  *calc_num1_pointer=0;
  *calc_num2_pointer=0;
  char proscess; 
  LCD_moveCursor(0,0);
  LCD_String("Calculator");
  LCD_moveCursor(1,0);
  LCD_Cmd(cursorBlink);
  int counter1=0;
  int counter2=0;
  int numbers[]=0;
  int numbers2[]=0;
  while(*calc_num1_pointer== 0){
    int readnumber= KEYPAD_getPressedKey();
    char readchar=KEYPAD_getPressedKey2();
    delay_ms(400);
    
    if ( readchar=='+'| readchar=='-'| readchar=='/'| readchar=='*'| readchar=='#' ){
      proscess=readchar;
      --counter1;
      for(int i = 0 ; i<=counter1 ; i++){
        
        int x=counter1-i;
        int y=pow(10,i);
        int z= numbers[counter1-i];
        *calc_num1_pointer=*calc_num1_pointer + z*y;
        
      }
      ++counter1;
      
    }
    else if (readchar=='='){}
    else{
      numbers[counter1]=readnumber;
      LCD_moveCursor(1,counter1);
      LCD_intgerToString(numbers[counter1]);
      ++counter1;
    }
  }
  LCD_moveCursor(1,counter1);
  LCD_Write_Char(proscess);
  ++counter1;
  while(*calc_num1_pointer!= 0 & *calc_num2_pointer==0){
    int readnumber= KEYPAD_getPressedKey();
    char readchar=KEYPAD_getPressedKey2();
    delay_ms(400);
    if (readchar=='=' ){
      --counter2;
      for(int i = 0 ; i<=counter2 ; i++){
        
        int x=counter2-i;
        int y=pow(10,i);
        int z= numbers2[counter2-i];
        *calc_num2_pointer=*calc_num2_pointer + z*y;
      }
    }
    else if( readchar=='+'| readchar=='-'| readchar=='/'| readchar=='*'| readchar=='#' ){}
    else{
      numbers2[counter2]=readnumber;
      LCD_moveCursor(1,counter1);
      LCD_intgerToString(numbers2[counter2]);
      ++counter1;
      ++counter2;
    }
    
  }
  float result;
  LCD_clearScreen();
  LCD_moveCursor(0,0);
  LCD_String("Calculator");
  LCD_moveCursor(1,0);
  LCD_String("=");
  LCD_moveCursor(1,1);
  switch (proscess){
  case '+':
    result=*calc_num1_pointer+*calc_num2_pointer;
    break;
  case '-':
    result=*calc_num1_pointer-*calc_num2_pointer;
    break;
  case '/':
    result=*calc_num1_pointer/ *calc_num2_pointer;
    break;
  case '*':
    result=*calc_num1_pointer* *calc_num2_pointer;
    break;
  }
  LCD_floatToString(result);
  LCD_Cmd(cursorOff);
  char readchar=KEYPAD_getPressedKey2();
  if ( readchar=='+'| readchar=='-'| readchar=='/'| readchar=='*'| readchar=='#' | readchar=='=' ){
    calculator_start();
  }
}
void stopwatch_pause(){
  TimerDisable(TIMER1_BASE,TIMER_A);
  LCD_moveCursor(0,9);
  
  LCD_String(" PAUSED");
}
void stopwatch_resume(){
  TimerEnable(TIMER1_BASE,TIMER_A);
  LCD_moveCursor(0,9);
  
  LCD_String("       ");
}
void stopwatch_reset_handler(void){
  stopwatch_reset(pointer_stopwatch_min,pointer_stopwatch_sec);
  
  LCD_moveCursor(1,0);
  LCD_intgerToString(0);
  LCD_moveCursor(1,1);
  LCD_intgerToString(0);
  LCD_moveCursor(1,3);
  LCD_intgerToString(0);
  LCD_moveCursor(1,4);
  LCD_intgerToString(0);
}
void stopwatch_reset(int* z, int* y){
  *y=0;
  *z=0;
}
void timer_start(void){
  LCD_clearScreen();
  LCD_moveCursor(0,0);
  LCD_String("Enter time");
  LCD_moveCursor(1,2);
  LCD_Write_Char(':');
  LCD_moveCursor(1,0);
  delay_ms(400);
  int min_1= KEYPAD_getPressedKey();
  LCD_intgerToString(min_1);
  LCD_moveCursor(1,1);
  delay_ms(400);
  int min_2=KEYPAD_getPressedKey();
  LCD_intgerToString(min_2);
  LCD_moveCursor(1,3);
  delay_ms(400);
  int sec_1= KEYPAD_getPressedKey();
  LCD_intgerToString(sec_1);
  LCD_moveCursor(1,4);
  delay_ms(400);
  int sec_2=KEYPAD_getPressedKey();
  LCD_intgerToString(sec_2);
  
  *pointer_sec= sec_1*10 + sec_2;
  *pointer_min= min_1*10 + min_2;
  *timer_status=1;
}
void timer_enable(void){
  TimerConfigure(TIMER0_BASE,TIMER_CFG_PERIODIC_UP); 
  TimerLoadSet(TIMER0_BASE,TIMER_A,16000000);
  TimerIntRegister(TIMER0_BASE,TIMER_A,timer_handler);
  TimerIntEnable(TIMER0_BASE,TIMER_TIMA_TIMEOUT);  
  TimerEnable(TIMER0_BASE,TIMER_A);
}
void timer_handler(void){
  
  TIMER0_ICR_R = 0x01;
  LCD_Cmd(clear_display);
  timer_counter(pointer_sec,pointer_min);
  LCD_Cmd(cursorOff);
}
void timer_counter(int *y, int* z){
  LCD_moveCursor(0,2);
  LCD_Write_Char(':');
  
  if(*z==0){
    if(*y>0){
      if(*y<10){
        LCD_moveCursor(0,0);
        LCD_intgerToString(0);
        LCD_moveCursor(0,1);
        LCD_intgerToString(*z);
        LCD_moveCursor(0,3);
        LCD_intgerToString(0);
        LCD_moveCursor(0,4);
        LCD_intgerToString(*y);
        --*y;
      }
      else {
        LCD_moveCursor(0,0);
        LCD_intgerToString(0);
        LCD_moveCursor(0,1);
        LCD_intgerToString(*z);
        LCD_moveCursor(0,3);
        LCD_intgerToString(*y);
        --*y;
      }
      
    }
    else if (*y==0){
      LCD_clearScreen();
      LCD_moveCursor(0,0);
      LCD_clearScreen();
      LCD_String("Done"); 
      TimerDisable(TIMER1_BASE,TIMER_A);
      
      TimerIntDisable(TIMER1_BASE,TIMER_TIMA_TIMEOUT);
      
      TimerIntUnregister(TIMER1_BASE,TIMER_A);
      TimerIntClear(TIMER1_BASE,TIMER_TIMA_TIMEOUT);  
    }
  }
  
  if(*z<10 & *z!=0){
    
    LCD_moveCursor(0,0);
    LCD_intgerToString(0);
    LCD_moveCursor(0,1);
    LCD_intgerToString(*z);
    
    if(*y<10 ){
      LCD_moveCursor(0,3);
      LCD_intgerToString(0);
      LCD_moveCursor(0,4);
      LCD_intgerToString(*y);
      --*y;
    }
    else if(*y>=10){
      LCD_moveCursor(0,3);
      LCD_intgerToString(*y);
      --*y;
    }
    if(*y<0){
      --*z;
      *y=59;
    }
  }
  else if(*z>=10){
    LCD_moveCursor(0,0);
    LCD_intgerToString(*z);
    
    if(*y<10){
      LCD_moveCursor(0,3);
      LCD_intgerToString(0);
      LCD_moveCursor(0,4);
      LCD_intgerToString(*y);
      --*y;
    }
    else if(*y>=10){
      LCD_moveCursor(0,3);
      LCD_intgerToString(*y);
      --*y;
    }
    if(*z>0 & *y<0 ){
      --*z;
      *y=59;
    }
  }
  
  
}
void stopwatch_start(void){
  LCD_clearScreen();
  LCD_moveCursor(0,0);
  LCD_String("Stopwatch");
  LCD_moveCursor(1,2);
  LCD_Write_Char(':');
  LCD_moveCursor(1,0);
  delay_ms(400);
  
  TimerConfigure(TIMER1_BASE,TIMER_CFG_PERIODIC_UP); 
  TimerLoadSet(TIMER1_BASE,TIMER_A,16000000);
  TimerIntRegister(TIMER1_BASE,TIMER_A,stopwatch_handler);
  TimerIntEnable(TIMER1_BASE,TIMER_TIMA_TIMEOUT);
  TimerEnable(TIMER1_BASE,TIMER_A);
  
}
void stopwatch_handler(void){
  LCD_Cmd(cursorOff);
  TIMER1_ICR_R = 0x01;
  stopwatch_counter(pointer_stopwatch_sec,pointer_stopwatch_min);
  LCD_Cmd(cursorOff);
}
void stopwatch_counter(int *y, int* z){
  LCD_moveCursor(1,2);
  LCD_Write_Char(':');
  if(*y<10 & *z<10){
    LCD_moveCursor(1,0);
    LCD_intgerToString(0);
    LCD_moveCursor(1,1);
    LCD_intgerToString(*z);
    LCD_moveCursor(1,3);
    LCD_intgerToString(0);
    LCD_moveCursor(1,4);
    LCD_intgerToString(*y);
  }
  if(*y==10 &*z<10){
    LCD_moveCursor(1,0);
    LCD_intgerToString(0);
    LCD_moveCursor(1,1);
    LCD_intgerToString(*z);
    LCD_moveCursor(1,3);
    LCD_intgerToString(0);
    LCD_moveCursor(1,3);
    LCD_intgerToString(*y);
  }
  if(*y<10 & *z>=10){
    LCD_moveCursor(1,0);
    LCD_intgerToString(*z);
    LCD_moveCursor(1,3);
    LCD_intgerToString(0);
    LCD_moveCursor(1,4);
    LCD_intgerToString(*y);
  }
  if(*y>10 & *z<10){
    LCD_moveCursor(1,0);
    LCD_intgerToString(0);
    LCD_moveCursor(1,1);
    LCD_intgerToString(*z);
    LCD_moveCursor(1,3);
    LCD_intgerToString(*y);
  }
  if(*y>=10 & *z>=10){
    LCD_moveCursor(1,0);
    LCD_intgerToString(*z);
    LCD_moveCursor(1,3);
    LCD_intgerToString(*y);
  }
  ++*y;
  if(*y==60){
    *y=0;
    ++*z;
  }
}
void stopwatch_end(void){
  LCD_Cmd(clear_display); 
  TimerIntUnregister(TIMER1_BASE,TIMER_A);
  TimerDisable(TIMER1_BASE,TIMER_A);
  TimerIntDisable(TIMER1_BASE,TIMER_TIMA_TIMEOUT);
  TimerIntUnregister(TIMER1_BASE,TIMER_A);
  TimerIntClear(TIMER1_BASE,TIMER_TIMA_TIMEOUT);
  *pointer_stopwatch_min=0;
  *pointer_stopwatch_sec=0;
  
}
void timer_end(void){
 TimerIntUnregister(TIMER0_BASE,TIMER_A);
  TimerDisable(TIMER0_BASE,TIMER_A);
  TimerIntDisable(TIMER0_BASE,TIMER_TIMA_TIMEOUT);
  TimerIntUnregister(TIMER0_BASE,TIMER_A);
  TimerIntClear(TIMER0_BASE,TIMER_TIMA_TIMEOUT);
  LCD_Cmd(clear_display);
  *timer_status=0;
  *pointer_min=0;
  *pointer_sec=0;
  
}