#include "timer.h"
#include "tm4c123gh6pm.h"

void init_timer(){
    SYSCTL_RCGCTIMER_R |= 0x01; //Use Timer A
    TIMER0_CTL_R = 0x0; //Disable Timer
    TIMER0_CFG_R = 0x0; // Configure as 32-bit register
    TIMER0_TAMR_R = 0x01; // Mode: One-shot
    }

void default_delay()
{
  delayMs(250);
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
