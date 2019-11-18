#include "tm4c123gh6pm.h"
#include "lcd_keypad.h"
#include "lcd_init.h"
#include "timer.h"
#include "stdbool.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"

char* keypad(){
  
  unsigned char arr[4][4] = {
    {'1', '2', '3', ' '},
    {'4', '5', '6', ' '},
    {'7', '8', '9', ' '},
    {' ', '0', ' ', ' '}
  }; // Only digits are needed
  bool while_stay = true; // Loop condition
  int column = 0;
  char x; // Digit to be sent to LCD
  char* str = (char*) malloc(sizeof(char) * 3); /* Save string of digits (like 100) to be iterated over, as local variables are deleted upon
  function end */
  unsigned int column_value = 0x00;
  GPIO_PORTE_DATA_R &= 0xF0;
  GPIO_PORTC_DATA_R |=0xF0; 
  
  while(while_stay){
  if((GPIO_PORTC_DATA_R &=0xF0)!=0xF0){ 
    
    // indication of which column was pressed
    
      column_value = GPIO_PORTC_DATA_R;
      if((GPIO_PORTC_DATA_R &= C_0)==0){
      column = 0;
      systick_delayMs(80);
      }
      else if((GPIO_PORTC_DATA_R &= C_1)==0){
      column = 1;
      systick_delayMs(80);
      }
      else if((GPIO_PORTC_DATA_R &= C_2)==0){
      column = 2;
      systick_delayMs(80);
      }
       else if((GPIO_PORTC_DATA_R &= C_3)==0){
      column = 3;
      systick_delayMs(80);
      }
     // function part to indicate which row was pressed 
  
      for(int j = 0; j < 4; j++){
      GPIO_PORTE_DATA_R |= 0x0F;
      GPIO_PORTE_DATA_R &= ~(0x01<<j);
      systick_delayMs(80);
         if(GPIO_PORTC_DATA_R == column_value){
           systick_delayMs(80);
           x = arr[j][column];
           if(x == ' '){ /* If x == space, exit loop (end of digits) */
           while_stay = false;
           }
           else{
           LCD_data(x); /* Send digit to LCD */
           strcat(str, &x); /* Add digit to string to know the whole number in the end and iterate over it*/
           }
        break;
        }
      }
  }
  // reset to default state 
  GPIO_PORTE_DATA_R &= 0xF0;
  GPIO_PORTC_DATA_R |= 0xF0;
  }
  return str;
}

void iterate(int n){
  char* str;
  int length;
  for(int i = n; i > -1; i--){
    sprintf(str, "%d", i); /* Convert integer to string */
    length = strlen(str);
    for(int j = 0; j < length; j++){
        LCD_data(*(str+j)); /* Send the digits to LCD*/
    }
    //systick_delayMs(250);
    LCD_command(1);
  }

}

void init_pc(){
//portC input (columns)
SYSCTL_RCGCGPIO_R |=SYSCTL_RCGCGPIO_R2;   // enable clock for portc
GPIO_PORTC_DEN_R |=  Port_enable; // enable all pins on portc
GPIO_PORTC_DIR_R &=  0x00; // set portc directions as inputs
GPIO_PORTC_PUR_R |= Port_enable;

}

void init_pe(){
//portE output (rows)
SYSCTL_RCGCGPIO_R |=SYSCTL_RCGCGPIO_R4;   // enable clock for porte
GPIO_PORTE_DEN_R |=  Port_enable; // enable porte pins 
GPIO_PORTE_DIR_R |=  Port_enable;// set porte directions as outputs
GPIO_PORTE_ODR_R |=  Port_enable;

}