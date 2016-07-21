#include<avr\io.h>
#define F_CPU 12000000ul
#include<util\delay.h>
#include <avr/interrupt.h>

#include "lcd.h"
#include "eeprom.h"
#include "keypad.h"
//#include "type.h"

#define SETBIT(reg,bit)  reg |=  (1<<bit)
#define CLRBIT(reg,bit)  reg &= ~(1<<bit)
#define TOGBIT(reg,bit)  reg ^=  (1<<bit)  //
#define rd_bit(reg,bit)  (reg &  (1<<bit))

void _display();

void IntToStr(u8_t x, u8_t *txt);

void initial_clock_value();

void timer1_second_init();

void get_new_time();
