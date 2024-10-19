#include "app/state_machine.h"
#include "drivers/uart.h"
#include "drivers/lcd.h"

e_state handle_false_start_state(void)
{
    uart_transmit("FALSE\r\n");
    lcd_add_to_rendering("\rFALSE START*****");

    return READY;
}