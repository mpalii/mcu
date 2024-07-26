/**
 * @author Maksym Palii
 * @brief Timer 0 (Fast PWM)
 * @version 2.0
*/

#include <avr/io.h>
#include "timer0.h"

/****************************************************************************/
/* Set up timer 0 for Fast PWM mode                                         */
/****************************************************************************/
void init_timer0(void)
{
    // TCCR0A – Timer/Counter0 Control Register channel A
    TCCR0A |= _BV(COM0A1) | _BV(WGM01) | _BV(WGM00);     // Clear OC0A on Compare Match, set OC0A at BOTTOM, (non-inverting mode).
	
    // TCCR0B – Timer/Counter0 Control Register channel B
    TCCR0B |= _BV(CS00);  // clk/1 (No prescaling)
	
    // OCR0A – Timer/Counter0 Output Compare Register channel A
    OCR0A =	0;
}

void set_duty(uint8_t duty)
{
    OCR0A = duty;
}