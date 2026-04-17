#define F_CPU 16000000UL
#include<avr/io.h>
#include<util/delay.h>

int main()
{
DDRB |= (1<<DDB5)|(1<<DDB4); //Configure Pin 4 and 5
PORTB |= (1<<PB5);
PORTB &=~(1<<PB4);
_delay_ms(5000);
PORTB &=~(1<<PB5);
PORTB&=~(1<<PB4);
_delay_ms(3000);
PORTB &=~(1<<PB5);
PORTB |=(1<<PB4);
_delay_ms(5000);
}
