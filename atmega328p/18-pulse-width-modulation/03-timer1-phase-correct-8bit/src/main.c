/**
 * @author Maksym Palii
 * @brief Phase correct PWM
 * @version 1.0
 * @date 2024 July 20
 */

#define F_CPU (8000000UL)

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

int main(void)
{
    // PB1 Alternate Function - OC1A (Timer/Counter1 Output Compare Match A Output)
    // Configure data direction for pins 1 (port B) as OUTPUT
    DDRB |= _BV(DDB1);

    // Waveform Generation Mode
    // Phase Correct PWM, 8-bit
    TCCR1B &= ~_BV(WGM13);
    TCCR1B &= ~_BV(WGM12);
    TCCR1A &= ~_BV(WGM11);
    TCCR1A |= _BV(WGM10);

    // Compare Output Mode, Fast PWM
    // Clear OC1A on Compare Match, set OC1A at BOTTOM (non-inverting mode)
    TCCR1A |= _BV(COM1A1);
    TCCR1A &= ~_BV(COM1A0);

    // Clock Select
    // clkIO/1 (No prescaling)
    TCCR1B &= ~_BV(CS12);
    TCCR1B &= ~_BV(CS11);
    TCCR1B |= _BV(CS10);

    // The duty cycle [0; 255]
    uint8_t duty = 0;

    // Utility boolean flag
    bool duty_cycle_increases = true;

    while (true)
    {
        OCR1A = duty;

        duty += duty_cycle_increases ? 1 : -1;

        if (duty == 255) 
            duty_cycle_increases = false;

        if (duty == 0)
            duty_cycle_increases = true;

        _delay_ms(10);
       
    }
}
