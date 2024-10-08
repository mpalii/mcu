/*
 * @author Maksym Palii
 * @brief UART speed test, MCU operating time
 * @version 1.0
 * @date 2023 June 15
 * 
 * 2400bps:     2x enabled - 4160ms;            2x disabled - 4160ms
 * 4800bps:     2x enabled - 2080ms;            2x disabled - 2080ms
 * 9600bps:     2x enabled - 1040ms;            2x disabled - 1040ms
 * 14.4kbps:    2x enabled - 690ms;             2x disabled - 680ms
 * 19.2kbps:    2x enabled - 520ms;             2x disabled - 520ms
 * 28.8kbps:    2x enabled - 340ms;             2x disabled - 340ms
 * 38.4kbps:    2x enabled - 260ms;             2x disabled - 260ms
 * 57.6kbps:    2x enabled - 170ms;             2x disabled - corrupted data
 * 76.8kbps:    2x enabled - 130ms;             2x disabled - corrupted data
 * 115.2kbps:   2x enabled - corrupted data;    2x disabled - corrupted data
 * 230.4kbps:   2x enabled - corrupted data;    2x disabled - corrupted data
 * 250kbps:     2x enabled - 40ms;              2x disabled - 40ms
 * 0.5Mbps:     2x enabled - 20ms;              2x disabled - 20ms
 * 1.0Mbps:     2x enabled - 10ms;              2x disabled - unsupported
 */

#define F_CPU 18432000UL

#include <avr/interrupt.h>
#include <stdio.h>
#include "uart328p.h"

void init_timer_0(void);

volatile uint32_t mcu_operating_time = 0;

char buffer[60];
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
        sprintf(buffer, "MCU operating time: %lums\r\nUART transmission took: %lums\r\n", mcu_operating_time, (finish_time - start_time));
        uart_transmit_array(buffer);
    }
}

/****************************************************************************/
/* Set up timer 0 for 1 mSec timebase                                       */
/* (64 (prescaler) * 125 (OCR0A + 1)) / 8_000_000 MHz = 0.001Sec = 1mSec    */
/****************************************************************************/
void init_timer_0(void)
{
    // TCCR0A – Timer/Counter0 Control Register channel A
    TCCR0A = _BV(WGM01);             // Clear Timer on Compare Match (CTC) mode (only works with channel)
	
    // TCCR0B – Timer/Counter0 Control Register channel B
    TCCR0B = _BV(CS01) | _BV(CS00);  // clk/64 (From prescaler)
	
    // OCR0A – Timer/Counter0 Output Compare Register channel A
    OCR0A =	124;                     //set the compare reg to 125 time ticks (zero based)
	
    // TIMSK0 – Timer/Counter0 Interrupt Mask Register
    TIMSK0 = _BV(OCIE0A);            // Timer/Counter0 Output Compare Match channel A Interrupt Enable
}
