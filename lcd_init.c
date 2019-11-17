#include "lcd_init.h"
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
void init_timer(){
    SYSCTL_RCGCTIMER_R |= 0x01; //Use Timer A
    TIMER0_CTL_R = 0x0; //Disable Timer
    TIMER0_CFG_R = 0x0; // Configure as 32-bit register
    TIMER0_TAMR_R = 0x01; // Mode: One-shot
    }

void default_delay()
{
  TIMER0_TAILR_R = 16000 * 250 - 1;
  delay();
}

void delayMs(int x){
  TIMER0_TAILR_R = 16000 * x - 1;
  delay();
}
 
void delayUs (int y){
  
  TIMER0_TAILR_R = 16 * y - 1;
  delay();
  
}

void delay(){
  TIMER0_CTL_R |= 0x01; /* Enable Timer A*/
  while ((TIMER0_RIS_R & 0x1) == 0) ;  /* Wait for TimerA timeout flag to set */
  TIMER0_ICR_R = 0x1;                  /* Clear the TimerA timeout flag */
  TIMER0_CTL_R &= ~(0x01); /* Disable Timer A*/ 

}

void LCD_command(unsigned char command)
{
    GPIO_PORTF_DATA_R &=  ~(EN | RS);     	/* RS = 0, R/W = 0 */
    GPIO_PORTB_DATA_R = command;
    GPIO_PORTF_DATA_R |= EN;    	/* pulse E */
    delayUs(1);		/* Enable pulse Width */
    GPIO_PORTF_DATA_R &= ~(EN | RS);
    if (command < 4)
        delayMs(2);         	/* command 1 and 2 needs up to 1.64ms */
    else
        delayUs(40);        /* all others 40 us */
}

void LCD_data(unsigned char data)
{
    GPIO_PORTF_DATA_R |= RS;    /* RS = 1, R/W = 0 */
    GPIO_PORTB_DATA_R = data;
    GPIO_PORTF_DATA_R |= (EN | RS);   /* pulse E */
    delayUs(1);
    GPIO_PORTF_DATA_R &= ~(EN | RS); 
    delayUs(40);
}

void LCD_start()
{
    delayMs(20);            /* initialization sequence */// Wait >15 ms after power is applied
    LCD_command(0x30);		// command 0x30 = Wake up
    delayMs(5);				// must wait 5ms, busy flag not available
    LCD_command(0x30);		// command 0x30 = Wake up #2
    delayUs(100);			// must wait 100us, busy flag not available
    LCD_command(0x30);		// command 0x30 = Wake up #3
    delayUs(100);			// must wait 100us, busy flag not available
  // Prepare LCD Operation and Function  
    LCD_command(0x38);      /* set 8-bit data, 2-line, 5x7 font */
    LCD_command(0x06);      /* move cursor right */
    LCD_command(0x01);      /* clear screen, move cursor to home */
    LCD_command(0x0F);      /* turn on display, cursor blinking */
}