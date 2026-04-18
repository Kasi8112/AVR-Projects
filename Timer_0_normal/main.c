#define F_CPU 16000000UL
#include<avr/io.h>
void delay_ms(int a)
{
while (a--)
{
TCNT0 = 0;
TCCR0A &= ~(1<<WGM00)|(1<<WGM01);
TCCR0B |= (1<<CS00)|(1<<CS01);
while (!(TIFR0 &(1<<TOV0)));
TIFR0 |= (1<<TOV0);
}
}
int main()
{
DDRB |= (1<<DDB5);
while (1){
PORTB ^=(1<<PB5);
delay_ms(2000);
}
}
