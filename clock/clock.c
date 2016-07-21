
#include "main.h"

typedef enum time_mode { AM = 1 ,PM = 2 ,Hour = 3 } AM_PM_HOUR;


struct clock 
{
u8_t second : 6; //bit field
u8_t minute : 6; //bit field
u8_t hour : 5;   //bit field
AM_PM_HOUR mode : 2; //bit field
} time;
 
#define second time.second
#define minute time.minute
#define hour   time.hour
#define mode   time.mode

#define CLR   '7'
#define set_timer '8'

#define up   '4'
#define down  '5'      

#define store  '1'
#define restore  '2'

#define stop_start '6'


extern S8_t push;

int main(void)
{
	DDRD |= 1;  // led toggle every 1 second
	
	keypad_init();

	lcd_init();

	lcd_sendcmd(clear);

	initial_clock_value();

	timer1_second_init();
    
	while(1)
	{
		keypad_click();
		if (push == stop_start){
			CLRBIT(TCCR1B,CS12);
		}
		else if (push == '3'){
			SETBIT(TCCR1B,CS12);
		}
		else if (push == CLR){
			second = 0;
			minute = 0;
			hour = 0;
		}
		else if (push == set_timer){
			CLRBIT(TCCR1B,CS12);
			lcd_sendcmd(clear);
			initial_clock_value();
			SETBIT(TCCR1B,CS12);
		}
		else if (push == restore){
			second = eeprom_read(0);
			minute = eeprom_read(1);
			hour   = eeprom_read(2);
		}
		else if (push == store){
			eeprom_write(second,0);
			eeprom_write(minute,1);
			eeprom_write(hour,2);
		}
	}
}

ISR (TIMER1_COMPA_vect)
{
    static u8_t t1 = 0;
//    _display();
	lcd_sendcmd(st_line);
	
	u8_t init_display[] = "Real Time clock by Sameh Afifi";
	u8_t temp[16];     
	u8_t size;


	// size of printed character 
	for ( size = 0; init_display[size] != '\0'; size++);
	
	if ( t1 <= (size - 16)){
		u8_t i;
		for ( i = t1; init_display[i] != '\0'; i++){
			temp[i-t1] = init_display[i];
		}
		
		lcd_sendstat(temp);
		
		t1++;
	}
	else if ((size - 16) < 0)
	lcd_sendstat(init_display);
	else
	t1 = 0;

		
	second++;
	if (second == 60)
	{
		second = 0;
		minute++;
		if (minute == 60)
		{
			minute = 0;
			hour++;
			if(mode == AM && hour == 12){
			   mode = PM;
			   hour = 0;
		    }
		    else if(mode == PM && hour == 12){
			   mode = AM;
			   hour = 0;
		    }
			if(hour == 24){
				hour = 0;
			}
		}
	}
	// toggle led here
		
	PORTD ^= (1 << 0);
    
	void (*update_time)();
	
	update_time = get_new_time;
	
	update_time();

}

/*
void _display(){
	lcd_sendcmd(st_line);
	
	u8 init_display[] = "Real Time clock by Sameh Afifi";
	u8 temp[16];
	u8 c;
	for ( c = 0; init_display[c] != '\0'; c++);
	
	if ( t1 <= (c - 16)){
		u8 i;
		for ( i = t1; init_display[i] != '\0'; i++){
			temp[i-t1] = init_display[i];
		}
		
		lcd_sendstat(temp);
		
		t1++;
	}
	else if ((c - 16) < 0)
	lcd_sendstat(init_display);
	else
	t1 = 0;
}
*/

void get_new_time(){
	u8_t txt[2];
	
	lcd_sendcmd(nd_line);
	IntToStr(hour, txt);
	lcd_senddata(txt[1]);
	lcd_senddata(txt[0]);

	IntToStr(minute, txt);
	lcd_senddata(':');
	lcd_senddata(txt[1]);
	lcd_senddata(txt[0]);

	IntToStr(second, txt);
	lcd_senddata(':');
	lcd_senddata(txt[1]);
	lcd_senddata(txt[0]);
	
	switch ( mode ){
	
	case  AM:     lcd_sendstat((u8_t*)"  AM    "); break;
	case  PM:     lcd_sendstat((u8_t*)"  PM    "); break;
	case  Hour:   lcd_sendstat((u8_t*)"  24Hour"); break;
	
	}	
}

void IntToStr(u8_t number, u8_t *txt){
	txt[0] = number % 10 + 48;
	txt[1] = number / 10 + 48;	
}		

void initial_clock_value(){
 
 	lcd_sendcmd(clear);
	//lcd_sendcmd(0x0c);
	lcd_sendcmd(st_line);
	lcd_sendstat((u8_t*)"Setting Time :");
	lcd_sendcmd(nd_line);
    //S8_t p;
	do {
		keypad_click();
		if (push == up)
		mode++;

		if (mode == 0)
		mode = 1;


		get_new_time();
	} while(push != '7');
	
	do {
		keypad_click();
		if (push == up)
		second++;
		if (push == down)
		second--;
		if (second == 60)
		second = 0;
		if (second == 63)
		second = 59;
		get_new_time();
	} while(push != '7');

	do {
		keypad_click();
		if (push == up)
		minute++;
		if (push == down)
		minute--;
		if (minute == 60)
		minute = 0;
		if (minute == 63)
		minute = 59;
		get_new_time();
	} while(push != '7');

	do {
		keypad_click();
		if (push == up)
		hour++;
		if (push == down)
		hour--;
		
		if (mode == 3){
			if (hour == 24)
			hour = 0;
			if (hour == 31)
			hour = 23;
		}
		if (mode == 1 || mode == 2){
			if (hour == 12)
			hour = 0;
			if (hour == 31)
			hour = 11;
		}
		get_new_time();
	} while(push != '7');	
}

void timer1_second_init(){
	TCCR1B |= (1 << WGM12)|(1 << CS12);

	// initialize compare value
	OCR1A = 46875;
	
	// enable compare interrupt
	TIMSK |= (1 << OCIE1A);
	
	// enable global interrupts
	sei();
}
