#include <stdlib.h>
#include <stdio.h>
#include "drivers/led.h"
#include "drivers/buzzer.h"
#include "drivers/uart.h"
#include "system/messages.h"
#include "system/metrics.h"

static char* response_message = NULL;

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
            response_message = led_toggle_enable_flag() ? serial_pattern_led_enabled : serial_pattern_led_disabled;
            break;

        case 'B':
        case 'b':
            response_message = buzzer_toggle_enable_flag() ? serial_pattern_buzzer_enabled : serial_pattern_buzzer_disabled;
            break;

        case '\r':
        case '\n':
            return;
        
        default:
            response_message = serial_pattern_unknown;
            break;
    }

    sprintf(text_buffer_serial, response_message);
    uart_add_to_buffer(text_buffer_serial);
}
