#define F_CPU 16000000UL
#include<avr/io.h>
#include<util/delay.h>
#include "lcd.h"

void enable_pulse()
{
PORTB |= (1<<PB3);
_delay_us(1);
PORTB &= ~(1<<PB3);
}

void send_byte(uint8_t byte, uint8_t rs){
if (rs==1)
{
PORTB |= (1<<PB4);
}
else
{
PORTB &= ~(1<<PB4); 
}
send_nibble(byte>>4);
_delay_ms(1);
send_nibble(byte & 0x0F);
}

void send_nibble(uint8_t nibble)
{
    PORTD &= 0x0F;            // Clear PD4-PD7, leave PD0-PD3 alone
/*    PORTD |= (nibble << 4);*/   // Shift nibble bits to the high pins
if(nibble & 0x08) PORTD|=(1<<PD7);
if(nibble & 0x04) PORTD|=(1<<PD6);   
if(nibble & 0x02) PORTD|=(1<<PD5);
if(nibble & 0x01) PORTD|=(1<<PD4);
enable_pulse();           // Latch the data
    _delay_us(100);           // Give the LCD controller time to process
}
void send_data(uint8_t data)
{
send_byte(data,1);
}

void send_cmd(uint8_t cmd)
{
send_byte(cmd,0);
}

void send_string(const char *str)
{
while(*str)
{
send_data(*str);
str++;
}
}

void lcd_init()
{
    // 1. Initial Power-up Delay
    _delay_ms(100); // 100ms is safer for simulations

    // 2. Set Pin Directions
    DDRD |= 0xF0;               // PD4, PD5, PD6, PD7 as output
    DDRB |= (1<<DDB3)|(1<<DDB4); // RS and EN as output[cite: 1]
    
    // 3. The "Attention" Sequence (forces controller into known state)
    send_nibble(0x03); 
    _delay_ms(5);     // Required delay > 4.1ms
    send_nibble(0x03); 
    _delay_us(150);   // Required delay > 100us
    send_nibble(0x03); 
    _delay_us(150);

    // 4. Finally switch to 4-bit mode
    send_nibble(0x02); 
    _delay_ms(2);

    // 5. Final Configuration Commands[cite: 1]
    send_cmd(0x28); // 4-bit mode, 2 lines, 5x8 font
    send_cmd(0x08); // Display OFF
    send_cmd(0x01); // Clear Display
    _delay_ms(3);   // Clear needs extra time
    send_cmd(0x06); // Entry Mode: Increment cursor
    send_cmd(0x0C); // Display ON, Cursor OFF

}

void clear_display()
{
send_cmd(0x01);
_delay_ms(3);
}

void return_home()
{
send_cmd(0x02);
_delay_ms(3);
}

void entry_mode()
{
send_cmd(0x06);
_delay_ms(3);
}

void set_cursor(uint8_t row, uint8_t col)
{
    uint8_t addr = (row == 0 ? 0x00 : 0x40) + col;
    send_cmd(0x80 | addr);
}
