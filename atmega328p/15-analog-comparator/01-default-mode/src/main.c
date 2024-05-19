/**
 * @author Maksym Palii
 * @brief Analog Comparator
 * @version 1.0
 * @date 2024 May 18
 */

#include <avr/io.h>
#include <stdbool.h>
#include "drivers/gpio.h"

int main(void)
{
    init_gpio();

    // ACSR |= _BV(ACD);

    while (true)
    {
        // When the voltage on the positive pin AIN0 is higher than the voltage on the negative pin AIN1
        if (bit_is_set(ACSR, ACO))
        {
            GPIO_HIGH(LED);
        }
        else
        {
            GPIO_LOW(LED);
        }
    }
}

