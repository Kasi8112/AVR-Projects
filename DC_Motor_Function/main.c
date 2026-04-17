#define F_CPU 16000000UL
#include<avr/io.h>
#include<util/delay.h>
void cw(int a);
void ccw(int b);
void stp(int c);
int main()
{
DDRB |=(1<<DDB5)|(1<<DDB4);
while(1)
{
cw(5000);
stp(3000);
ccw(5000);
stp(3000);
}
}
void cw(int a)
{
PORTB |=(1<<PB5);
PORTB &=~(1<<PB4);
while(a--)
{
_delay_ms(1);
}
}

void ccw(int b)
{
PORTB &=~(1<<PB5);
PORTB |=(1<<PB4);
while (b--)
{
_delay_ms(1);
}
}

void stp(int c)
{
PORTB &=~(1<<PB5);
PORTB &=~(1<<PB4);
while (c--)
{
_delay_ms(1);
}
}
