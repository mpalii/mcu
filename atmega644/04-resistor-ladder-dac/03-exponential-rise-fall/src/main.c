/**
 * @author Maksym Palii
 * @brief DAC (r2r resistor ladder)
 * @date 2024 September 21
 */

#define F_CPU           (18432000UL)
#define MAX_AMPLITUDE   (0xFFFF)
#define TAU_RISE        (8)
#define TAU_FALL        (8)

#include "drivers/gpio.h"   
#include <util/delay.h>

int main(void) 
{
    init_gpio();

    uint16_t amplitude_rise = MAX_AMPLITUDE;
    uint16_t amplitude_fall = MAX_AMPLITUDE;

    while (true)
    {
        // Exponential rise: form (1-exp(-t/tau))
        amplitude_rise = amplitude_rise - (amplitude_rise >> TAU_RISE);
        uint8_t rise = (MAX_AMPLITUDE - amplitude_rise) >> 8;

        // Exponential fall: form (exp(-t/tau))
        amplitude_fall = amplitude_fall - (amplitude_fall >> TAU_FALL);
        uint8_t fall = amplitude_fall >> 8;

        DAC = ((uint16_t) rise * fall) >> 8;

        _delay_ms(2);
    } 
}
