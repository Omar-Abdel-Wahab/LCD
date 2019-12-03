#include "lcd_init.h"
#include "timer.h"
#include "lcd_keypad.h"
#include "tm4c123gh6pm.h"
#include "stdlib.h"

void lcd_test()
{
  init_pf();
  init_pb();
  //init_timer();
  LCD_start();
  char names [4][8]={"Monica ","Kirolos ","Omar ","ElKady "};
  volatile int count =-1;
  char x, z;
  while(1){
  if ((GPIO_PORTF_DATA_R & sw1)==0)
  {
    count++;
    if (count==4){
      count=0;
    }
     LCD_command(1);
     systick_default_delay();
     
     volatile int i=0;
     while((names[count][i])!= ' ')
    {
     x=names[count][i];
    LCD_data(x);
    i++;
    }
   
  }
  if ((GPIO_PORTF_DATA_R & sw2)==0)
  {
     count--;
    if (count<0){
      count=3;
    }
     LCD_command(1);
    systick_default_delay();
    
   volatile int j=0;
   while(names[count][j]!= ' ')
   {
     z=names[count][j];
    LCD_data(z);
    j++;
      }
    }
  
  }
}

void welcome(){
  char cs[] = "Number:";
    for(int i = 0; i < 7; i++){
    LCD_data(cs[i]);
  }  
    
}    
void keypad_lcd_test()
{
  init_pf();
  init_pb();
  init_pc();
  init_pe();
  LCD_start();
  init_timer();
  LCD_command(1);
  iterate_stopwatch();
  //welcome();
  //char* str = keypad();
  //LCD_command(1);
  //int n = atoi(str); /* Convert string to integer */
  //iterate(n);
}

int main()
{ 
  //lcd_test();
  keypad_lcd_test();
  return 0;
} 