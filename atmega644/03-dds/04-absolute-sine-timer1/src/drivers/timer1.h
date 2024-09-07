#ifndef TIMER1_H_
#define TIMER1_H_

#include <avr/io.h>

/****************************************************************************/
/* Set up timer 1 for 17.75 uSec timebase                                   */
/* (1 (prescaler) * 284 (OCR1A + 1)) / 16_000_000 MHz = 0.00001775Sec       */
/****************************************************************************/
inline void init_timer1(void)
{
    // TCCR1B – Timer/Counter1 Control Register channel B
    TCCR1B |= _BV(WGM12);    // Clear Timer on Compare Match (CTC)

    // TCCR1B – Timer/Counter1 Control Register channel B
    TCCR1B |= _BV(CS10);     // Start timer1 (No prescaling)
	
    // OCR1A – Timer/Counter1 Output Compare Register channel A
    OCR1A = 283;		     // Set the compare reg to 284 ticks (zero based)
	
    // TIMSK1 – Timer/Counter1 Interrupt Mask Register
    TIMSK1 = _BV(OCIE1A);    // Timer/Counter0 Output Compare Match channel A Interrupt Enable
}

#endif /* TIMER1_H_ */