/*
 * 08_UART_speedTest.c
 * It takes 1039 ms to transmit 1000 characters with baud rate 9600 bps
 * It takes 173 ms to transmit 1000 characters with baud rate 57600 bps
 * It takes 86 ms to transmit 1000 characters with baud rate 115200 bps
 * It takes 43 ms to transmit 1000 characters with baud rate 230400 bps
 *
 * Created: 18/02/2023 23:44:26
 * Author : Maksym_Palii
 */

#define F_CPU 18432000UL

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "uart328p.h"

void init_timer_0(void);

volatile uint32_t operation_time = 0;

char buffer[50];
char *message_1000_chars =
"...................................................................................................."
"...................................................................................................."
"...................................................................................................."
"...................................................................................................."
"...................................................................................................."
"...................................................................................................."
"...................................................................................................."
"...................................................................................................."
"...................................................................................................."
"..................................................................................................\r\n";

ISR (TIMER0_COMPA_vect)
{
    operation_time++;
}

int main(void)
{
    init_timer_0();
    sei();
    UART_init(F_CPU, 230400, false);
 
    uint32_t start_time = operation_time;
    UART_transmit_array(message_1000_chars);
    uint32_t finish_time = operation_time;
 
    sprintf(buffer, "TX time: %lu ms\r\n", (finish_time - start_time));
    UART_transmit_array(buffer);
 
    while (true)
    {
        // NOP
    }
}

/****************************************************************************/
/* Set up timer 0 for 1 mSec timebase                                       */
/* (256 (prescaler) * 72 (OCR0A + 1)) / 18_432_000 MHz = 0.001Sec = 1mSec   */
/****************************************************************************/
void init_timer_0(void)
{
    // TCCR0A – Timer/Counter0 Control Register channel A
    TCCR0A = _BV(WGM01);             // Clear Timer on Compare Match (CTC) mode (only works with channel)
	
    // TCCR0B – Timer/Counter0 Control Register channel B
    TCCR0B = _BV(CS02);  // clk/256 (From prescaler)
	
    // OCR0A – Timer/Counter0 Output Compare Register channel A
    OCR0A =	71;                     //set the compare reg to 72 time ticks (zero based)
	
    // TIMSK0 – Timer/Counter0 Interrupt Mask Register
    TIMSK0 = _BV(OCIE0A);            // Timer/Counter0 Output Compare Match channel A Interrupt Enable
}
