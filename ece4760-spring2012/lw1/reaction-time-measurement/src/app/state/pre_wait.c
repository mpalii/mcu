// #include <stdlib.h>
#include "drivers/uart.h"
#include "drivers/lcd.h"
#include "app/state_machine.h"
#include "app/metrics.h"
#include "app/events.h"

e_state handle_pre_wait_state(void)
{
    uart_transmit("WAIT\r\n");
    lcd_add_to_rendering("\rWAIT************");

    // srand((unsigned int) mcu_operating_time);
    // delay = 999 + (rand() % 60000);
    delay = 9999 + (mcu_operating_time % 55000);
    fast_track_mode = true;
    user_reaction_time = 0;

    return WAIT;
}