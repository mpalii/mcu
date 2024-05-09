/**
 * @author Maksym Palii
 * @brief ADC auto triggering mode
 * @version 1.0
 * @date 2024 May 9
 */

#include <stdbool.h>
#include "drivers/gpio.h"
#include "drivers/cx56.h"
#include "drivers/timer0.h"
#include "task_manager.h"

int main(void)
{
    init_gpio();
    init_cx56();
    init_timer0();
    init_adc();
    init_tasks();
    sei();
	
    while (true)
    {
        handle_tasks();
    }
}
