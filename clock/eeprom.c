#include "eeprom.h"
#define setbit(a,b)  a |= 1 << b
#define clrbit(a,b)  a &= ~(1 << b)
#define togbit(a,b)  a ^= 1 << b
#define rd_bit(a,b)  (a & (1 << b))

void eeprom_write(unsigned char data,unsigned int addr ){
	while(rd_bit(EECR,1));
	EEAR = addr;
	EEDR = data;
	setbit(EECR,2);  // protection to eeprom
	setbit(EECR,1);
}

unsigned char eeprom_read(unsigned int addr ){
	while(rd_bit(EECR,1));
	EEAR = addr;
	setbit(EECR,0);
	return EEDR;

}
int check_count(unsigned char counter){
	if(counter == 100)
	return 0;
	if(counter == 255)
	return 99;
	return counter;
}

void seven_seg(unsigned char counter){
	unsigned char temp;
	
	temp = counter % 10;
	setbit(temp,4);
	clrbit(temp,5);
	PORTC = temp;
	
	_delay_ms(1);
	
	temp = counter / 10;
	setbit(temp,5);
	clrbit(temp,4);
	PORTC = temp;
	
	_delay_ms(1);
}
