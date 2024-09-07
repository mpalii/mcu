/**
 * @author Maksym Palii
 * @brief Timer 0 (Fast PWM)
*/

#include <avr/io.h>
#include "timer0.h"

/****************************************************************************/
/* Set up timer 0 for Fast PWM mode                                         */
/* 16_000_000Hz / 256 = 62_500Hz; 62_500Hz / 64 = 976.56Hz                  */
/****************************************************************************/
void init_timer0(void)
{
    // TCCR0A – Timer/Counter0 Control Register channel A
    TCCR0A |= _BV(WGM01) | _BV(WGM00);                  // Waveform Generation Mode - Fast PWM
    
    // TCCR0A – Timer/Counter0 Control Register channel A
    TCCR0A |= _BV(COM0A1);                              // Clear OC0A on Compare Match, set OC0A at BOTTOM, (non-inverting mode)
	
    // TCCR0B – Timer/Counter0 Control Register channel B
    TCCR0B |= _BV(CS01) | _BV(CS00);                    // Start Timer 0 with clk/64
}

void set_duty(uint8_t duty)
{
    OCR0A = duty;
}