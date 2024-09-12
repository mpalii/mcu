#ifndef TIMER1_H_
#define TIMER1_H_

#include <avr/io.h>

/****************************************************************************/
/* Set up timer 1 for 61 uSec timebase (16_384 Hz)                          */
/* (1 (prescaler) * 1125 (OCR1A + 1)) / 18_432_000 MHz = 0.000061Sec        */
/****************************************************************************/
inline void init_timer1(void)
{
    // TCCR1B – Timer/Counter1 Control Register channel B
    TCCR1B |= _BV(WGM12);    // Clear Timer on Compare Match (CTC)

    // TCCR1B – Timer/Counter1 Control Register channel B
    TCCR1B |= _BV(CS10);     // Start timer1 (No prescaling)
	
    // OCR1A – Timer/Counter1 Output Compare Register channel A
    OCR1A = 1124;		     // Set the compare reg to 1125 ticks (zero based)
	
    // TIMSK1 – Timer/Counter1 Interrupt Mask Register
    TIMSK1 = _BV(OCIE1A);    // Timer/Counter0 Output Compare Match channel A Interrupt Enable
}

#endif /* TIMER1_H_ */