#include <stdlib.h>
#include <stdio.h>
#include "drivers/led.h"
#include "drivers/buzzer.h"
#include "drivers/uart.h"
#include "system/messages.h"
#include "system/metrics.h"

static char* response_pattern = NULL;

void handle_serial_input(void)
{
    char input = uart_read();

    if (input == 0)
    {
        return;
    }

    switch (input)
    {
        case 'L':
        case 'l':
            response_pattern = led_toggle_enable_flag() ? LED_ENABLED : LED_DISABLED;
            break;

        case 'B':
        case 'b':
            response_pattern = buzzer_toggle_enable_flag() ? BUZZER_ENABLED : BUZZER_DISABLED;
            break;

        case '\r':
        case '\n':
            return;
        
        default:
            response_pattern = UNKNOWN;
            break;
    }

    sprintf(text_buffer_serial, response_pattern, (mcu_operating_time / 10));
    uart_add_to_buffer(text_buffer_serial);
}
