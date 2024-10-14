/**
 * @author Maksym Palii
 * @brief Reaction time measurement
 * @version 1.0
 * @date 2024 October 14
 * @link https://people.ece.cornell.edu/land/courses/ece4760/labs/s2012/lab1.html
 */

#include <stdbool.h>
#include "drivers/gpio.h"
#include "drivers/uart.h"
#include "drivers/led.h"
#include "drivers/button.h"
#include "drivers/reset.h"
#include "drivers/lcd.h"
#include "drivers/timer2.h"
#include "drivers/timer1.h"
#include "drivers/timer0.h"

int main(void)
{
    init_gpio();
    init_uart();
    init_led();
    init_button();
    init_reset();
    init_lcd();
    init_timer2();
    init_timer1();
    init_timer0();

    while (true)
    {
        // TODO
    }

    return 0;
}