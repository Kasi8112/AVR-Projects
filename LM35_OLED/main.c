#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define OLED_ADDR 0x3C

// ================= I2C =================
void i2c_init() {
    TWSR = 0x00;
    TWBR = 72; // 100kHz @ 16MHz
    TWCR = (1 << TWEN);
}

void i2c_start() {
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
}

void i2c_stop() {
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void i2c_write(uint8_t data) {
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
}

// ================= OLED =================
void oled_cmd(uint8_t cmd) {
    i2c_start();
    i2c_write(OLED_ADDR << 1);
    i2c_write(0x00);
    i2c_write(cmd);
    i2c_stop();
}

void oled_data(uint8_t data) {
    i2c_start();
    i2c_write(OLED_ADDR << 1);
    i2c_write(0x40);
    i2c_write(data);
    i2c_stop();
}

void oled_clear() {
    for (uint16_t i = 0; i < 1024; i++) {
        oled_data(0x00);
    }
}

// ================= OLED INIT =================
void oled_init() {
    _delay_ms(100);

    oled_cmd(0xAE);
    oled_cmd(0x20); oled_cmd(0x10);
    oled_cmd(0xB0);
    oled_cmd(0xC8);
    oled_cmd(0x00);
    oled_cmd(0x10);
    oled_cmd(0x40);
    oled_cmd(0x81); oled_cmd(0x7F);
    oled_cmd(0xA1);
    oled_cmd(0xA6);
    oled_cmd(0xA8); oled_cmd(0x3F);
    oled_cmd(0xD3); oled_cmd(0x00);
    oled_cmd(0xD5); oled_cmd(0xF0);
    oled_cmd(0xD9); oled_cmd(0x22);
    oled_cmd(0xDA); oled_cmd(0x12);
    oled_cmd(0xDB); oled_cmd(0x20);
    oled_cmd(0x8D); oled_cmd(0x14);
    oled_cmd(0xAF);

    oled_clear();
}

// ================= SIMPLE FONT (6x8 minimal ASCII) =================
const uint8_t font[10][6] = {
    {0x3E,0x51,0x49,0x45,0x3E,0}, // 0
    {0x00,0x42,0x7F,0x40,0x00,0}, // 1
    {0x42,0x61,0x51,0x49,0x46,0}, // 2
    {0x21,0x41,0x45,0x4B,0x31,0}, // 3
    {0x18,0x14,0x12,0x7F,0x10,0}, // 4
    {0x27,0x45,0x45,0x45,0x39,0}, // 5
    {0x3C,0x4A,0x49,0x49,0x30,0}, // 6
    {0x01,0x71,0x09,0x05,0x03,0}, // 7
    {0x36,0x49,0x49,0x49,0x36,0}, // 8
    {0x06,0x49,0x49,0x29,0x1E,0}  // 9
};

// ================= PRINT CHAR =================
void oled_char(char c) {

    if (c >= '0' && c <= '9') {
        const uint8_t *f = font[c - '0'];
        for (int i = 0; i < 6; i++) oled_data(f[i]);
    }
    else if (c == 'T' || c == ':' || c == 'C') {
        for (int i = 0; i < 6; i++) oled_data(0x00);
    }
    else {
        for (int i = 0; i < 6; i++) oled_data(0x00);
    }
}

// ================= PRINT STRING =================
void oled_print(char *str) {
    while (*str) {
        oled_char(*str++);
    }
}

// ================= ADC =================
void adc_init() {
    ADMUX = (1 << REFS0); // AVCC reference, ADC0 selected
    ADCSRA = (1 << ADEN)
           | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t adc_read(uint8_t ch) {
    ADMUX = (ADMUX & 0xF0) | (ch & 0x0F);
    _delay_ms(2);
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC));
    return ADC;
}

// ================= MAIN =================
int main(void) {

    char buf[20];
    uint16_t adc;
    float voltage, temp;

    adc_init();
    i2c_init();
    oled_init();

    while (1) {

        adc = adc_read(0); // LM35 on PC0

        voltage = (adc * 5.0) / 1024.0;
        temp = voltage * 100.0;

        sprintf(buf, "T:%dC", (int)temp);

        oled_cmd(0xB0);
        oled_cmd(0x00);
        oled_cmd(0x10);

        oled_print(buf);

        _delay_ms(1000);
    }
}