#include "drivers/lcd.h"
#include "drivers/uart.h"
#include "system/messages.h"
#include "system/state_machine.h"

e_state handle_pre_ready_state(void)
{
    uart_add_to_buffer(text_buffer_serial);
    lcd_add_to_rendering(text_buffer_lcd);

    uart_enable_rx();

    return READY;
}