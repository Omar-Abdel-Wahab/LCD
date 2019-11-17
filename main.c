#include "lcd_init.h"
#include "tm4c123gh6pm.h"

void lcd_test()
{
  init_pf();
  init_pb();
  init_timer();
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
     default_delay();
     
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
    default_delay();
    
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

int main()
{ 
  lcd_test();
  return 0;
} 