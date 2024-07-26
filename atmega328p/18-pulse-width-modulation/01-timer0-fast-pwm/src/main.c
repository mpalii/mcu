/*
 * @author Maksym Palii
 * @brief Fast PWM
 * @version 1.0
 * @date 2024 July 14
 */
#define F_CPU (8000000UL)

#include "drivers/gpio.h"
#include "drivers/timer0.h"
#include <util/delay.h>
#include <stdbool.h>

int main(void)
{
    // // PB1 Alternate Function - OC1A (Timer/Counter1 Output Compare Match A Output)
    // // Configure data direction for pins 1 (port B) as OUTPUT
    // DDRB |= _BV(DDB1);

    // // Waveform Generation Mode
    // // Fast PWM, 8-bit
    // TCCR1B &= ~_BV(WGM13);
    // TCCR1B |= _BV(WGM12);
    // TCCR1A &= ~_BV(WGM11);
    // TCCR1A |= _BV(WGM10);

    // // Compare Output Mode, Fast PWM
    // // Clear OC1A on Compare Match, set OC1A at BOTTOM (non-inverting mode)
    // TCCR1A |= _BV(COM1A1);
    // TCCR1A &= ~_BV(COM1A0);

    // // Clock Select
    // // clkIO/1 (No prescaling)
    // TCCR1B &= ~_BV(CS12);
    // TCCR1B &= ~_BV(CS11);
    // TCCR1B |= _BV(CS10);

    init_gpio();
    init_timer0();

    

    while (true)
    {
        for (uint8_t duty = 0; duty < 255; duty++)
        {
            // OCR1A = duty;
            set_duty(duty);
            _delay_ms(5);
        }

        for (uint8_t duty = 255; duty > 0; duty--)
        {
            // OCR1A = duty;
            set_duty(duty);
            _delay_ms(10);
        }

        // OCR1A = 0;
            set_duty(0);

        _delay_ms(5000);
    }
}