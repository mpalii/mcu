/*
 * @author Maksym Palii
 * @brief ADC free running mode with hysteresis
 * @version 1.0
 * @date 2024 May 6
 */

#include "drivers/gpio.h"
#include "drivers/adc.h"
#include <avr/interrupt.h>
#include <stdbool.h>

#define LOWER_LIMIT (256UL)
#define UPPER_LIMIT (LOWER_LIMIT * 3)

uint16_t conversion_result = 0;

ISR(ADC_vect)
{
    conversion_result = ADC;
}

int main(void)
{
    gpio_init();
    adc_init();
    sei();

    while (true) 
    { 
        if (conversion_result >= UPPER_LIMIT)
        {
            GPIO_LOW(LED);
        }

        if (conversion_result < LOWER_LIMIT)
        {
            GPIO_HIGH(LED);
        }
    }
}
