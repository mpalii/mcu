#include "app/state_machine.h"
#include "drivers/uart.h"
#include "drivers/lcd.h"

e_state handle_timeout_state(void)
{
    uart_transmit("TIMEOUT\r\n");
    lcd_add_to_rendering("\rTIMEOUT*********");

    return READY;
}