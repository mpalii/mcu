/**
 * @author Maksym Palii
 * @brief Timer 0 (system timer)
 * @version 2.0
*/

#include <avr/io.h>
#include "timer0.h"

/****************************************************************************/
/* Set up timer 0 for 8 mSec timebase                                       */
/* (1024 (prescaler) * 250 (OCR0A + 1)) / 8_000_000 MHz = 0.032Sec = 32mSec */
/****************************************************************************/
void init_timer0(void)
{
    // TCCR0A – Timer/Counter0 Control Register channel A
    TCCR0A = _BV(WGM01);             // Clear Timer on Compare Match (CTC) mode (only works with channel)
    // TCCR0B – Timer/Counter0 Control Register channel B
    TCCR0B = _BV(CS02) | _BV(CS00);  // clk/1024 (From prescaler)
    // OCR0A – Timer/Counter0 Output Compare Register channel A
    OCR0A =	249;                     //set the compare reg to 250 time ticks (zero based)
    // TIMSK0 – Timer/Counter0 Interrupt Mask Register
    TIMSK0 = _BV(OCIE0A);            // Timer/Counter0 Output Compare Match channel A Interrupt Enable
}