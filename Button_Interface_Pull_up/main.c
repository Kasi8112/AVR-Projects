#define F_CPU 16000000UL
#include<avr/io.h>
#include<util/delay.h>

int main()
{
DDRB |= (1<<DDB5);
DDRB &= ~(1<<DDB4);
PORTB |= (1<<PB4); 
while(1)
{
if (PINB & (1<<PB4))
{
PORTB &= ~(1<<PB5);
}
else
{
PORTB |= (1<<PB5);
}
}
}
