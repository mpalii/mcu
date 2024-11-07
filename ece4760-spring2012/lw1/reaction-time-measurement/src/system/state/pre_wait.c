#include <stdio.h>
#include "drivers/lcd.h"
#include "drivers/uart.h"
#include "system/events.h"
#include "system/messages.h"
#include "system/metrics.h"
#include "system/state_machine.h"

e_state handle_pre_wait_state(void)
{
    sprintf(text_buffer_lcd, lcd_pattern_wait);
    sprintf(text_buffer_serial, serial_pattern_wait, delay);

    lcd_add_to_rendering(text_buffer_lcd);
    uart_add_to_buffer(text_buffer_serial);

    return WAIT;
}