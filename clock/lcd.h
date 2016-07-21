
#include "type.h"

#define clear 0x01
#define home  0x02
#define inc_cur_left 0x04
#define inc_cur_right 0x06

#define shift_cur_left 0x10
#define shift_cur_right 0x14
#define shift_display_left 0x18
#define shift_display_right 0x1c

#define nd_line 0xc0
#define st_line 0x80

// configure LCD port
extern void lcd_init();

// to  send command to LCD
extern void lcd_sendcmd(unsigned char cmd);

// to  send data to LCD
extern void lcd_senddata(unsigned char cmd);

// send complete word
extern void lcd_sendstat(unsigned char *word);