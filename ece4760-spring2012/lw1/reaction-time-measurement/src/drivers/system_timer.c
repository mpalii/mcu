#include "gpio.h"
#include "uart.h"

/**
 * @brief Timer 0 is used as a SYSTEM TIMER with 0.001s (1.0ms) precision
 * @warning dont forget about appropriate interruption service routine ISR (TIMER0_COMPA_vect)
 * @see task_manager/scheduler.c
 */

/****************************************************************************/
/* Set up timer 0 for 1 ms timebase                                         */
/* (64 (prescaler) * 250 (OCR0A + 1)) / 16_000_000 MHz = 0.001s = 1.0ms     */
/****************************************************************************/
void init_system_timer(void)
{
    // TCCR0A - Timer/Counter0 Control Register channel A
    TCCR0A = _BV(WGM01);            // Clear Timer on Compare Match (CTC) mode (only works with channel)
	
    // OCR0A - Timer/Counter0 Output Compare Register channel A
    OCR0A =	249;                    // Set the compare reg to 250 time ticks (zero based)
	
    // TIMSK0 - Timer/Counter0 Interrupt Mask Register
    TIMSK0 = _BV(OCIE0A);           // Timer/Counter0 Output Compare Match channel A Interrupt Enable

    uart_transmit("- SYSTEM TIMER ready\r\n");
}

void system_timer_start(void)
{
    // TCCR0B - Timer/Counter0 Control Register channel B
    TCCR0B = _BV(CS01) | _BV(CS00); // clk/64 (From prescaler)
}

void system_timer_stop(void)
{
    // TCCR0B - Timer/Counter0 Control Register channel B
    TCCR0B &= ~(_BV(CS01) | _BV(CS00)); // clk/64 (From prescaler)
}