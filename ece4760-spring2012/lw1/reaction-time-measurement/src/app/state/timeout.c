#include "../state_machine.h"
#include "../tasks/button_handler.h"
#include "../../drivers/uart.h"
#include "../../drivers/lcd.h"
#include <stdbool.h>

static bool is_ready_for_transition = false;

e_state handle_timeout_state(void)
{
    if (!is_ready_for_transition)
    {
        uart_transmit("TIMEOUT\r\n");
		lcd_add_to_rendering("\rTIMEOUT***********");
		is_ready_for_transition = true;
    }
	
    if (get_button_event() && is_ready_for_transition)
    {
        is_ready_for_transition = false;
        return READY;
    }

    return TIMEOUT;
}