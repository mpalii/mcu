#include "gpio.h"

/**
 * @brief Timer 0 is used as a SYSTEM TIMER with 0.001s precision
 * @warning dont forget about appropriate interruption service routine ISR (TIMER0_COMPA_vect)
 * @see task_manager/scheduler.c
 */

/****************************************************************************/
/* Set up timer 0 for 1 ms timebase                                         */
/* (1024 (prescaler) * 18 (OCR0A + 1)) / 18_432_000 MHz = 0.001s = 1ms      */
/****************************************************************************/
void init_timer0(void)
{
    // TCCR0A - Timer/Counter0 Control Register channel A
    TCCR0A = _BV(WGM01);            // Clear Timer on Compare Match (CTC) mode (only works with channel)

    // TCCR0B - Timer/Counter0 Control Register channel B
    TCCR0B = _BV(CS02) | _BV(CS00); // clk/1024 (From prescaler)
	
    // OCR0A - Timer/Counter0 Output Compare Register channel A
    OCR0A =	17;                     //set the compare reg to 18 time ticks (zero based)
	
    // TIMSK0 - Timer/Counter0 Interrupt Mask Register
    TIMSK0 = _BV(OCIE0A);           // Timer/Counter0 Output Compare Match channel A Interrupt Enable
}