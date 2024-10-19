#include <stdio.h>
#include "drivers/lcd.h"
#include "drivers/uart.h"
#include "app/messages.h"
#include "app/metrics.h"
#include "app/state_machine.h"

e_state handle_pre_ready_state(void)
{
    sprintf(text_buffer_serial, READY_SERIAL_PATTERN, (mcu_operating_time / 10));
    uart_add_to_buffer(text_buffer_serial);

    sprintf(text_buffer_lcd, READY_LCD_PATTERN, (high_score / 10), (high_score % 10));
    lcd_add_to_rendering(text_buffer_lcd);

    return READY;
}