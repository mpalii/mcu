#include "app/state_machine.h"
#include "drivers/uart.h"
#include "drivers/lcd.h"

e_state handle_pre_ready_state(void)
{
    uart_transmit("READY\r\n");
    lcd_add_to_rendering("\rREADY***********");

    return READY;
}