/*
 * @author Maksym Palii
 * @brief UART speed test, MCU operating time
 * @version 1.0
 * @date 2023 June 17
 * 
 * 2400bps:     2x enabled - 4166/4167ms;       2x disabled - 4166/4167ms
 * 4800bps:     2x enabled - 2083/2084ms;       2x disabled - 2083/2084ms
 * 9600bps:     2x enabled - 1041/1042ms;       2x disabled - 1041/1042ms
 * 14.4kbps:    2x enabled - 694/695ms;         2x disabled - 694/695ms
 * 19.2kbps:    2x enabled - 520/521ms;         2x disabled - 520/521ms
 * 28.8kbps:    2x enabled - 347/348ms;         2x disabled - 347/348ms
 * 38.4kbps:    2x enabled - 260/261ms;         2x disabled - 260/261ms
 * 57.6kbps:    2x enabled - 173/174ms;         2x disabled - 173/174ms
 * 76.8kbps:    2x enabled - 130/131ms;         2x disabled - 130/131ms
 * 115.2kbps:   2x enabled - 86/87ms;           2x disabled - 86/87ms
 * 230.4kbps:   2x enabled - 43/44ms;           2x disabled - 43/44ms
 * 250kbps:     2x enabled - 39/40ms;           2x disabled - corrupted data
 * 0.5Mbps:     2x enabled - corrupted data;    2x disabled - unsupported
 * 1.0Mbps:     2x enabled - unsupported;       2x disabled - unsupported
 * 1.152Mbps:   2x enabled - 8/9ms;             2x disabled - 8/9ms
 */

#define F_CPU 18432000UL

#include <avr/interrupt.h>
#include <stdlib.h>
#include "uart328p.h"

void init_timer_0(void);

volatile uint32_t mcu_operating_time = 0;

char time_buffer[21];
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
    mcu_operating_time++;
}

int main(void)
{
    init_timer_0();
    sei();
    uart_init(F_CPU, 2400, false);
    
    uart_transmit_array("Start up...\r\n");
 
    while (true)
    {    
        uint32_t start_time = mcu_operating_time;
        uart_transmit_array(message_1000_chars);
        uint32_t finish_time = mcu_operating_time;

        ultoa(mcu_operating_time, time_buffer, 10);
        uart_transmit_array("MCU operating time: ");
        uart_transmit_array(time_buffer);
        uart_transmit_array("ms\r\n");

        itoa((finish_time - start_time), time_buffer, 10);
        uart_transmit_array("UART transmission took: ");
        uart_transmit_array(time_buffer);
        uart_transmit_array("ms\r\n");
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
