#include "lcd_init.h"
#include "timer.h"
#include "tm4c123gh6pm.h"

void init_pf()
{
//CLOCK
SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;

//UNLOCK
GPIO_PORTF_LOCK_R = 0x4C4F434B;
GPIO_PORTF_CR_R |= 0X1F;

//ENABLE
GPIO_PORTF_DEN_R |= (RS | RW | EN | sw1| sw2);

//DIRECTION
GPIO_PORTF_DIR_R |= (RS | RW | EN);
GPIO_PORTF_DIR_R &= ~(sw1 | sw2);

//PULL-UP
GPIO_PORTF_PUR_R |= (sw1|sw2);}

void init_pb()
{
  //CLOCK
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;
  //DIRECTION
  GPIO_PORTB_DIR_R |= 0xFF;
  //ENABLE
  GPIO_PORTB_DEN_R |= 0xFF;
}

void LCD_command(unsigned char command)
{
    GPIO_PORTF_DATA_R &=  ~(EN | RS);     	/* RS = 0, R/W = 0 */
    GPIO_PORTB_DATA_R = command;
    GPIO_PORTF_DATA_R |= EN;    	/* pulse E */
    systick_delayUs(1);		/* Enable pulse Width */
    GPIO_PORTF_DATA_R &= ~(EN | RS);
    if (command < 4)
        systick_delayMs(2);         	/* command 1 and 2 needs up to 1.64ms */
    else
        systick_delayUs(40);        /* all others 40 us */
}

void LCD_data(unsigned char data)
{
    GPIO_PORTF_DATA_R |= RS;    /* RS = 1, R/W = 0 */
    GPIO_PORTB_DATA_R = data;
    GPIO_PORTF_DATA_R |= (EN | RS);   /* pulse E */
    systick_delayUs(1);
    GPIO_PORTF_DATA_R &= ~(EN | RS); 
    systick_delayUs(40);
}

void LCD_start()
{
    systick_delayMs(20);            /* initialization sequence */// Wait >15 ms after power is applied
    LCD_command(0x30);		// command 0x30 = Wake up
    systick_delayMs(5);				// must wait 5ms, busy flag not available
    LCD_command(0x30);		// command 0x30 = Wake up #2
    systick_delayUs(100);			// must wait 100us, busy flag not available
    LCD_command(0x30);		// command 0x30 = Wake up #3
    systick_delayUs(100);			// must wait 100us, busy flag not available
  // Prepare LCD Operation and Function  
    LCD_command(0x38);      /* set 8-bit data, 2-line, 5x7 font */
    LCD_command(0x06);      /* move cursor right */
    LCD_command(0x01);      /* clear screen, move cursor to home */
    LCD_command(0x0F);      /* turn on display, cursor blinking */
}