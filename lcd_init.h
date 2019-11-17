#ifndef LCD_DEFINITIONS
#define LCD_DEFINITIONS

#define sw1 0x10
#define sw2 0x01
#define RS 0x02
#define RW 0x04
#define EN 0x08


void init_pf();
void init_pb();

void LCD_command(unsigned char command);
void LCD_data(unsigned char data);
void LCD_start();

#endif