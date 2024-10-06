#ifndef TIMER0_H_
#define TIMER0_H_

#include <util/delay.h>

/****************************************************************************/
/* Set up timer 0 for Fast PWM mode                                         */
/* 18_432_000Hz / 256 = 72_000Hz;                                           */
/****************************************************************************/
void init_timer0(void)
{
    // TCCR0A – Timer/Counter0 Control Register channel A
    TCCR0A |= _BV(WGM01) | _BV(WGM00);                  // Waveform Generation Mode - Fast PWM
    
    // TCCR0A – Timer/Counter0 Control Register channel A
    TCCR0A |= _BV(COM0A1);                              // Clear OC0A on Compare Match, set OC0A at BOTTOM, (non-inverting mode)
	
    // TCCR0B – Timer/Counter0 Control Register channel B
    TCCR0B |= _BV(CS00);                                // Start Timer 0 (with clk/1 no prescaling)

    // smoothly increase analog output to avoid clicks
    for (uint8_t i = 0; i < 128; i++)
    {
        OCR0A = i;
        _delay_ms(0.5);
    }
}

inline void set_duty(uint8_t duty)
{
    OCR0A = duty;
}

#endif /* TIMER0_H_ */