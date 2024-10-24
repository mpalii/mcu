#include "drivers/lcd.h"
#include "drivers/uart.h"
#include "system/messages.h"
#include "system/state_machine.h"

e_state handle_pre_ready_state(void)
{
    uart_add_to_buffer(text_buffer_serial);
    lcd_add_to_rendering(text_buffer_lcd);

    // // hack to clear buffer
    // if (uart_read() == 0)
    // {
    //     asm("nop"::);
    // }

    uart_enable_rx();

    return READY;
}