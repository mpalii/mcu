/**
 * @author Maksym Palii
 * @brief Reaction time measurement
 * @version 1.0
 * @date 2024 October 13
 * @link https://people.ece.cornell.edu/land/courses/ece4760/labs/s2012/lab1.html
 */

#include <stdbool.h>
#include "drivers/gpio.h"
#include "drivers/uart.h"
#include "drivers/timer2.h"

#include <util/delay.h>

int main(void)
{
    init_gpio();
    init_uart();
    init_timer2();

    while (true)
    {
        // TODO
    }

    return 0;
}