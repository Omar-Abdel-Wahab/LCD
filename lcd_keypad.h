#ifndef LCD_KEYPAD
#define LCD_KEYPAD

#define Port_enable 0xFF
#define C_0 0x10
#define C_1 0x20
#define C_2 0x40
#define C_3 0x80


char* keypad();
void init_pc();
void init_pe();
void iterate(int n);
void iterate_stopwatch();

#endif