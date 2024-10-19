#include <stdio.h>
#include "drivers/lcd.h"
#include "drivers/uart.h"
#include "app/messages.h"
#include "app/metrics.h"
#include "app/state_machine.h"

e_state handle_false_start_state(void)
{
    sprintf(text_buffer_serial, FALSE_START_SERIAL_PATTERN, (mcu_operating_time / 10));
    uart_add_to_buffer(text_buffer_serial);

    lcd_add_to_rendering(FALSE_START_LCD_MESSAGE);

    return READY;
}