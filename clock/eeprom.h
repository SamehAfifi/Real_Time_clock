#include <avr/io.h>
#define F_CPU 12000000ul
#include<util/delay.h>


void inits(void);
void seven_seg(unsigned char x);
void eeprom_write(unsigned char data,unsigned int addr );
unsigned char  eeprom_read(unsigned int addr );
int  check_count(unsigned char counter);