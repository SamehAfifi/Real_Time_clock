

#include<avr\io.h>
#define F_CPU 12000000ul
#include<util\delay.h>

#include "type.h"
//#include "keypad.h"
#include "keypad_config.h"


#define SETBIT(reg,bit)  reg |=  (1<<bit)
#define CLRBIT(reg,bit)  reg &= ~(1<<bit)
#define TOGBIT(reg,bit)  reg ^=  (1<<bit)
#define rd_bit(reg,bit)  (reg &  (1<<bit))


S8_t push = 0;
	
u8_t keypad_matrix[]={
	'1','2','3',
	'4','5','6',
	'7','8','9',
};

void keypad_init(){
	mykeypadport
	pullup
}

S8_t press(S8_t i){

	if(!k4 ){
	return keypad_matrix[0+i*3];
	}
	
	if(!k5 ){
	return keypad_matrix[1+i*3];
	}
	
	if(!k6){
	return keypad_matrix[2+i*3];
	}	
	
	_delay_ms(10);
	
	return -1;
}

S8_t keypad_press(){

    S8_t k;
	
	k1(0);k2(1);k3(1);
	k = press(0);
	if(k != -1)
	return k;

	k1(1);k2(0);k3(1);
	k = press(1);
	if(k != -1)
	return k;

	k1(1);k2(1);k3(0);
	k = press(2);
	if(k != -1)
	return k;

	return -1;
}

void keypad_click(){

	static S8_t k;
	if (keypad_press() != k){
		k = keypad_press();
		push = k;
	}
	else
	    push = -1;
}