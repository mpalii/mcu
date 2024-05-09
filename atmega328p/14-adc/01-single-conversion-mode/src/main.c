/*
 * @author Maksym Palii
 * @brief ADC single conversion mode with hysteresis
 * @version 1.0
 * @date 2024 April 26
 */

#include "drivers/gpio.h"
#include "drivers/adc.h"
#include <stdbool.h>

#define LOWER_LIMIT (256UL)
#define UPPER_LIMIT (LOWER_LIMIT * 3)

int main(void)
{
    gpio_init();
    adc_init();
    adc_start_conversion();

    while (true) 
    { 
        if (ADCSRA & (_BV(ADIF)))
        {
            uint16_t conversion_result = ADC;

            if (conversion_result >= UPPER_LIMIT)
            {
                GPIO_LOW(LED);
            }

            if (conversion_result < LOWER_LIMIT)
            {
                GPIO_HIGH(LED);
            }
            
            adc_start_conversion();
        }
    }
}
