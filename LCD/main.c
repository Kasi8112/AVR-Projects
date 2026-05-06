#define F_CPU 16000000UL
#include<avr/io.h>
#include<util/delay.h>
#include "lcd.h"
int main()
{
lcd_init();
clear_display();
set_cursor(0,0);
_delay_ms(100);
send_string("Hello");
while(1){
}
}
