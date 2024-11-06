#include "gpio.h"
#include "uart.h"

/****************************************************************************/
/* Set up timer 1 for 1.0s timebase                                         */
/* (256 (prescaler) * 62500 (OCR0A + 1)) / 16_000_000 MHz = 1.0s            */
/****************************************************************************/
void init_reaction_timer(void)
{
    // OCR1A - Timer/Counter1 Output Compare Register channel A
    OCR1A =	62499;          // Set the compare reg to 62500 time ticks (zero based)
	
    // TIMSK0 - Timer/Counter1 Interrupt Mask Register
    TIMSK1 = _BV(OCIE1A);   // Timer/Counter1 Output Compare Match channel A Interrupt Enable

    uart_transmit("- REACTION TIMER ready\r\n");
}

void reaction_timer_start(void)
{
    // Reset counter
    TCNT1 = 0;
    // clk/256 (From prescaler)
    TCCR1B |= _BV(CS12);
}

uint16_t reaction_timer_stop(void)
{
    // stop timer 1
    TCCR1B &= ~_BV(CS12);
    return (uint16_t) TCNT1;
}