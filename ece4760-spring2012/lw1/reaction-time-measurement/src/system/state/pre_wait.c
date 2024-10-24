#include <stdio.h>
#include <stdlib.h>
#include "drivers/lcd.h"
#include "drivers/uart.h"
#include "system/events.h"
#include "system/messages.h"
#include "system/metrics.h"
#include "system/state_machine.h"

e_state handle_pre_wait_state(void)
{
    srand((unsigned int) mcu_operating_time);
    delay = 10000 + (rand() % 55535);
    fast_track_mode = true;
    user_reaction_time = 0;

    sprintf(text_buffer_serial, WAIT_SERIAL_PATTERN, (mcu_operating_time / 10), (delay / 10), (delay % 10));
    sprintf(text_buffer_lcd, WAIT_LCD_MESSAGE);

    uart_add_to_buffer(text_buffer_serial);
    lcd_add_to_rendering(text_buffer_lcd);

    return WAIT;
}