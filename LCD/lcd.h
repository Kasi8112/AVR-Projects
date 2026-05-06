#ifndef LCD_H
#define LCD_H

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>


void lcd_init(void);
void clear_display(void);
void return_home(void);


void send_cmd(uint8_t cmd);
void send_data(uint8_t data);


void send_string(const char *str);


void send_byte(uint8_t data, uint8_t rs);
void send_nibble(uint8_t nibble);
void enable_pulse(void);
void set_cursor(uint8_t row, uint8_t col);

#endif
