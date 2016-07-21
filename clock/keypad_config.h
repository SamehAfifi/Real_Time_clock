#ifndef  key
#define key

#define mykeypadport  DDRD |= 7<<2;
#define pullup  PORTD = 0b11100000;
// Keypad configurations
#define k1(x)   if (x == 0) CLRBIT(PORTD,2); else SETBIT(PORTD,2);
#define k2(x)   if (x == 0) CLRBIT(PORTD,3); else SETBIT(PORTD,3);
#define k3(x)   if (x == 0) CLRBIT(PORTD,4); else SETBIT(PORTD,4);

#define k4  (PIND &  (1<<5))
#define k5  (PIND &  (1<<6))
#define k6  (PIND &  (1<<7))


#endif