#include "app/state_machine.h"
#include "app/metrics.h"
#include "drivers/uart.h"
#include "drivers/lcd.h"
#include <stdlib.h>

#define RADIX   (10)

static char lcd_buffer[6] = { '\r', 0, 0, 0, 0, 0 };
static char* result_substring = ((char*) lcd_buffer) + 1;

e_state handle_result_state(void)
{
    uart_transmit("RESULT\r\n");
    itoa(user_reaction_time, result_substring, RADIX);
    lcd_add_to_rendering(lcd_buffer);

    return READY;
}