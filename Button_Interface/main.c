#define F_CPU 16000000UL
#include<avr/io.h>
#include<util/delay.h>

int main()
{
DDRD &=~(1<<DDD5);
DDRD |=(1<<DDD4);
while(1){
if (PIND & (1<<PD5))
{
PORTD |=(1<<PD4);
} 
else
{
PORTD &=~(1<<PD4);
}
}
}
