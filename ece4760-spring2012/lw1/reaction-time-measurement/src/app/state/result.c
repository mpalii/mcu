#include "../state_machine.h"
#include "../tasks/button_handler.h"
#include "../../drivers/uart.h"
#include "../../drivers/lcd.h"
#include "../metrics.h"
#include <stdbool.h>
#include <stdlib.h>

static bool is_ready_for_transition = false;
static char lcd_buffer[17] = { 0 };

e_state handle_result_state(void)
{
    if (!is_ready_for_transition)
    {
        uint16_t result = get_reaction_time();
        ultoa(result, lcd_buffer, 10);
        uart_transmit("RESULT\r\n");
		lcd_add_to_rendering("\rRESULT***********");
		is_ready_for_transition = true;
    }
	
    if (get_button_event() && is_ready_for_transition)
    {
        is_ready_for_transition = false;
        return READY;
    }

    return RESULT;
}