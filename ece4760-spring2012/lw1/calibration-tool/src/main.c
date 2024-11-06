/**
 * @author Maksym Palii
 * @brief Calibration device for reaction time tester
 * @version 1.0
 * @date 2024 October 24
 */

#define F_CPU (20000000ULL)

#include <avr/interrupt.h>
#include <stdbool.h>
#include <util/delay.h>
#include "drivers/gpio.h"

ISR (INT0_vect)
{    
    // GPIO_LOW(LED);

    _delay_ms(128);
    // _delay_ms(40);
    // _delay_ms(4.4);
    // _delay_us(8);
    GPIO_LOW(BUTTON_TRIGGER);
    _delay_ms(200);
    GPIO_HIGH(BUTTON_TRIGGER);

    // GPIO_HIGH(LED);
}

int main(void)
{
    gpio_init();

    EICRA |= _BV(ISC01);    // The falling edge of INT0 generates an interrupt request.
    EIMSK |= _BV(INT0);

    sei();
	
    while (true)
    {
        // NOP
    }
}
