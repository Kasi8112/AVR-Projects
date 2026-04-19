#define F_CPU 16000000UL
#include<avr/io.h>

void delay_ms(int a)
{

OCR0A = 249;
TCCR0A |= (1<<WGM01);
TCCR0A &= ~(1<<WGM00);
TCCR0B |= (1<<CS00)|(1<<CS01);

while(a--)
{
TCNT0 = 0;
while(!(TIFR0 &(1<<OCF0A)));
TIFR0 |= (1<<OCF0A);
}
}

int main()

{
while(1)
{
DDRB |=(1<<DDB5);
PORTB ^= (1<<PB5);
delay_ms(1000);
}
}
