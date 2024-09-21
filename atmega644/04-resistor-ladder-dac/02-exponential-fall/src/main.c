/**
 * @author Maksym Palii
 * @brief DAC (r2r resistor ladder)
 * @date 2024 September 21
 */

#define F_CPU           (18432000UL)
#define MAX_AMPLITUDE   (0xFFFF)
#define TAU             (8)

#include "drivers/gpio.h"   
#include <util/delay.h>

int main(void) 
{
    init_gpio();

    uint16_t amplitude_fall = MAX_AMPLITUDE;

    while (true)
    {
        // Exponential fall: form (exp(-t/tau))
        amplitude_fall = amplitude_fall - (amplitude_fall >> TAU);
        DAC = amplitude_fall >> 8;

        _delay_ms(2);
    } 
}
