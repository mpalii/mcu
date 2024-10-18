#include "gpio.h"
#include "uart.h"

/**
 * Actually nothing to init.
 * Timer 1 is used in Normal Mode
 */
void init_timer1(void)
{
    uart_transmit("- Timer 1 ready\r\n");
}

void timer1_start(void)
{
    TCNT1 = 0;
    TCCR1B |= (_BV(CS12) | _BV(CS10));  // 1024 prescaler
}

uint16_t timer1_stop(void)
{
    TCCR1B &= ~(_BV(CS12) | _BV(CS10));
    return (uint16_t) TCNT1;
}