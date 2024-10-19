#include <stdio.h>
#include "drivers/lcd.h"
#include "drivers/uart.h"
#include "app/messages.h"
#include "app/metrics.h"
#include "app/state_machine.h"

e_state handle_timeout_state(void)
{
    sprintf(text_buffer_serial, TIMEOUT_SERIAL_PATTERN, (mcu_operating_time / 10));
    uart_transmit(text_buffer_serial);

    lcd_add_to_rendering(TIMEOUT_LCD_MESSAGE);

    return READY;
}