#include "app/state_machine.h"
#include "app/metrics.h"
#include "app/events.h"
#include "drivers/led.h"
#include "drivers/timer2.h"

e_state handle_wait_state(void)
{
    if (button_event)
    {
        button_event = false;
        fast_track_mode = false;
        return FALSE_START;
    }

    if (delay == 0)
    {
        led_on();
        timer2_start();
        return MEASURING;
    }

    delay--;
    return WAIT;
}