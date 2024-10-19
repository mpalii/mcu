#include <stdio.h>
#include "drivers/lcd.h"
#include "drivers/uart.h"
#include "app/messages.h"
#include "app/metrics.h"
#include "app/state_machine.h"


e_state handle_result_state(void)
{
    sprintf(text_buffer_serial, RESULT_SERIAL_PATTERN, (mcu_operating_time / 10), (user_reaction_time / 10), (user_reaction_time % 10));
    uart_add_to_buffer(text_buffer_serial);

    sprintf(text_buffer_lcd, RESULT_LCD_PATTERN, (user_reaction_time / 10), (user_reaction_time % 10));
    lcd_add_to_rendering(text_buffer_lcd);

    return READY;
}