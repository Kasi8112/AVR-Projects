#define F_CPU 16000000UL
#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>

ISR(INT0_vect)
{
PORTD ^= (1<<PD4);
}

int main()
{
DDRB |= (1<<DDB5);
DDRD |= (1<<DDD4);
DDRD &= ~(1<<DDD2);
PORTD |= (1<<PD2);
EIMSK |= (1<<INT0);
EIFR |= (1<<INTF0);
EICRA |= (1<<ISC01); 
EICRA &= ~(1<<ISC00);
sei();
while(1)
{
PORTB ^=(1<<PB5);
_delay_ms(1000);
}
}
