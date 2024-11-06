#include "drivers/lcd.h"
#include "system/events.h"
#include "system/messages.h"
#include "system/metrics.h"
#include "system/state_machine.h"

e_state handle_wait_state(void)
{
    if (button_event)
    {
        button_event = false;
        fast_track_mode = false;

        text_buffer_serial = serial_pattern_false_start;
        text_buffer_lcd = lcd_pattern_false_start;

        return AFTER_FAST_MODE;     // stabilization needs
    }

    if (delay == 0)
    {
        return MEASURING;
    }

    delay--;
    return WAIT;
}