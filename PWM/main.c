#define F_CPU 16000000UL
#include<avr/io.h>
#include<util/delay.h>

int main()
{
DDRD |= (1 << DDD6);
TCCR0A |= (1<<WGM00)|(1<<WGM01); //FAST PWM SET
TCCR0A |= (1<<COM0A1); //NON-INVERTING
TCCR0B |= (1<<CS00)|(1<<CS01); // 64 PRESCALAR
for (int i=0;i<=255;i++)
{
OCR0A = i;
_delay_ms(100);
}

for (int i=255;i>=50;i--)
{
OCR0A = i; 
_delay_ms(100); 
}

while(1){}
}
