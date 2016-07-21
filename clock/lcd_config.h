// LCD configurations
#ifndef xxx

#include<avr\io.h>
#define F_CPU 12000000ul
#include<util\delay.h>

#define xxx

#define MyLCDport  DDRB |= (15<<4); DDRA |= (7<<4)

#define EN(x)   if (x == 0) CLRBIT(PORTA,7); else SETBIT(PORTA,7);
#define Rw(x)   if (x == 0) CLRBIT(PORTA,6); else SETBIT(PORTA,6);
#define RS(x)   if (x == 0) CLRBIT(PORTA,5); else SETBIT(PORTA,5);

#define D7(x)   if (x == 0) CLRBIT(PORTB,7); else SETBIT(PORTB,7);
#define D6(x)   if (x == 0) CLRBIT(PORTB,6); else SETBIT(PORTB,6);
#define D5(x)   if (x == 0) CLRBIT(PORTB,5); else SETBIT(PORTB,5);
#define D4(x)   if (x == 0) CLRBIT(PORTB,4); else SETBIT(PORTB,4);

#endif