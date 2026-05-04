#define F_CPU 16000000UL
#include<avr/io.h>
#include<util/delay.h>

int main()
{
char data = 'A';
UCSR0C &= ~(1<<UMSEL00) | (1<<UMSEL01);
UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00);
UBRR0L = 103;
UCSR0B |= (1<<TXEN0);

while(1){
while(!(UCSR0A & (1<<UDRE0)));
UDR0 = data;
_delay_ms(1000);
}
}
