#include "drivers/lcd.h"
#include "drivers/uart.h"
#include "system/events.h"
#include "system/messages.h"
#include "system/state_machine.h"

e_state handle_pre_wait_state(void)
{

    text_buffer_serial = get_serial_wait_message();
    text_buffer_lcd = lcd_pattern_wait;

    uart_add_to_buffer(text_buffer_serial);
    lcd_add_to_rendering(text_buffer_lcd);

    return WAIT;
}