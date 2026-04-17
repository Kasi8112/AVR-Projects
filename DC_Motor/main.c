#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

// ================= PWM INIT (Timer1) =================
void pwm_init() {
    // Set PB1 (OC1A) and PB2 (OC1B) as output
    DDRB |= (1 << PB1) | (1 << PB2);

    // Fast PWM mode, non-inverting
    TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11);
    TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11); // prescaler 8

    ICR1 = 20000; // 50Hz base (can be used for DC motor fine control)
}

// Set speed (0–100%)
void set_speed(uint8_t speed) {
    uint16_t value = (speed * 20000) / 100;

    OCR1A = value; // Motor A speed
    OCR1B = value; // Motor B speed
}

// ================= MOTOR CONTROL PINS =================
void motor_init() {
    DDRD |= (1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5);
}

// ================= MOVEMENTS =================

void forward() {
    PORTD |= (1 << PD2);
    PORTD &= ~(1 << PD3);

    PORTD |= (1 << PD4);
    PORTD &= ~(1 << PD5);
}

void reverse() {
    PORTD &= ~(1 << PD2);
    PORTD |= (1 << PD3);

    PORTD &= ~(1 << PD4);
    PORTD |= (1 << PD5);
}

void left() {
    PORTD &= ~(1 << PD2);
    PORTD |= (1 << PD3);

    PORTD |= (1 << PD4);
    PORTD &= ~(1 << PD5);
}

void right() {
    PORTD |= (1 << PD2);
    PORTD &= ~(1 << PD3);

    PORTD &= ~(1 << PD4);
    PORTD |= (1 << PD5);
}

void stop() {
    PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5));
}

// ================= MAIN =================
int main(void) {

    motor_init();
    pwm_init();

    set_speed(70); // 70% speed

    while (1) {

        forward();
        _delay_ms(2000);

        stop();
        _delay_ms(1000);

        reverse();
        _delay_ms(2000);

        stop();
        _delay_ms(1000);

        left();
        _delay_ms(1500);

        right();
        _delay_ms(1500);

        stop();
        _delay_ms(2000);
    }
}
