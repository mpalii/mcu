#include "gpio.h"
#include "uart.h"

/**
 * @brief Timer 2 is used for sound generation with ~880Hz pitch
 * @see drivers/gpio.h and // TODO add location
 */

/****************************************************************************/
/* Set up Timer/Counter2 for ~440Hz frequency generation                    */
/* the passive buzzer will generate sound with ~880Hz pitch                 */
/* (256 (prescaler) * 82(OCR2A + 1)) / 18_432_000 Hz = 0.001139s            */
/****************************************************************************/
void init_timer2(void)
{
    // TCCR2A - Timer/Counter2 Control Register channel A
    TCCR2A |= _BV(WGM21); // Waveform Generation Mode - CTC

    // OCR2A - Timer/Counter2 Output Compare Register channel A
    OCR2A = 81; //set the compare reg to 82 ticks (zero based)
	
    // TCCR2B - Timer/Counter2 Control Register channel B - clkT2S/256
    TCCR2B |= _BV(CS22) | _BV(CS21);

    // Configure GPIO
    _gpio_set_output(BUZZER);

    uart_transmit("- Timer 2 ready\r\n");
}

void timer2_start(void)
{
    // TCCR2A - Timer/Counter2 Control Register channel A
    TCCR2A |= _BV(COM2A0);  // Enable OC2A toggling on compare match
}

void timer2_stop(void)
{
    // TCCR2A - Timer/Counter2 Control Register channel A
    TCCR2A &= ~_BV(COM2A0); // Normal port operation, OC2A disconnected
	
    // System can stop Timer/Counter2 when pin will be driven high
    _gpio_low(BUZZER);
}