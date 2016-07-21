
#include "lcd.h"

/*
CMD :
1  // clr screen
2  // return to 0,0 line

4  // DEC  cursor shift cursor left
6  // INC  cursor shift cursor right

5  // shift display left
7  // shift display right

8  // display and cursor off
A  // display off cursor on
C  // display on cursor off
E  // display on cursor on

10 // shift cursor pos to left
14 // shift cursor pos to right

18 // shift display left
1C // shift display right

80 //force cursor to beginning of 1st line
C0 //force cursor to beginning of 2nd line

*/

#include "lcd.h"
#include "lcd_config.h"



#define SETBIT(reg,bit)  reg |=  (1<<bit)
#define CLRBIT(reg,bit)  reg &= ~(1<<bit)
#define TOGBIT(reg,bit)  reg ^=  (1<<bit)
#define rd_bit(reg,bit)  (reg &  (1<<bit))


void lcd_new_data(){
	EN(1);
	_delay_ms(1);
	EN(0);
	_delay_ms(1);
}

void lcd_reset(){
	for(int i = 0 ; i < 3; i++){
		
		D7(1);D6(1);D5(1);D4(1);
		
		_delay_ms(20);
		
		D7(0);D6(0);D5(1);D4(1);
		
		lcd_new_data();
	}
	D7(0);D6(0);D5(1);D4(0);
	
	lcd_new_data();
}

void lcd_init4bitmode(){
	lcd_reset();
	_delay_ms(5);
	lcd_sendcmd(0x28);  // 4data line
	lcd_sendcmd(clear);
	lcd_sendcmd(0x0c);  // display on cursor off
	lcd_sendcmd(0x06);  // increment cursor right
	lcd_sendcmd(0x80);  // set courser at the beginning of the first line
	_delay_ms(20);
}

void lcd_init(){
	MyLCDport;
	Rw(0);  
	lcd_init4bitmode();
}

void lcd_read(unsigned char cmd){
	// read first 4 bit
	D7(0); D6(0);D5(0); D4(0);
	D7(rd_bit(cmd,7));
	D6(rd_bit(cmd,6));
	D5(rd_bit(cmd,5));
	D4(rd_bit(cmd,4));

	lcd_new_data();

	// read second 4 bit
	D7(0); D6(0);D5(0); D4(0);
	D7(rd_bit(cmd,3));
	D6(rd_bit(cmd,2));
	D5(rd_bit(cmd,1));
	D4(rd_bit(cmd,0));

	lcd_new_data();
}


void lcd_sendcmd(unsigned char cmd){
	RS(0); // Rs = 0
    lcd_read(cmd);
}

void lcd_senddata(unsigned char cmd){
	RS(1); // Rs = 1
    lcd_read(cmd);
}


void lcd_sendstat(u8_t *x){
    for(int i = 0; x[i] != '\0'; i++){
    	RS(1); // Rs = 1
	    lcd_read(x[i]);
	}	
}