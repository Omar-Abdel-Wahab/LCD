#ifndef TIMER
#define TIMER

void delayMs(int x);
void delayUs(int y);
void init_timer();
void default_delay();
void delay();
void systick_default_delay();
void systick_delay();
void systick_delayMs(int x);
void systick_delayUs(int y);

#endif
