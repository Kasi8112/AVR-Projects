#define F_CPU 16000000UL
#include<avr/io.h>
#include<util/delay.h>

int main()
{
DDRB |= (1<<DDB5); // Configured Pin 5 as output
while(1){
PORTB |=(1<<PB5); // Pin 5 = High
_delay_ms(300); //Delay of 1s
PORTB &=~(1<<PB5); // Pin 5 = Low
_delay_ms(300);
}

}
