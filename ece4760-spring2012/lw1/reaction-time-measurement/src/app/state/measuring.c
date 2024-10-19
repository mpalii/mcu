#include <app/state_machine.h>
#include <app/metrics.h>
#include <app/events.h>
#include "drivers/led.h"
#include "drivers/timer2.h"

e_state handle_measuring_state(void)
{
    if (button_event)
    {
        button_event = false;
        fast_track_mode = false;        
        led_off();
        timer2_stop();
        return RESULT;
    }

    if (user_reaction_time == 10000)
    {
        fast_track_mode = false;
        led_off();
        timer2_stop();
        return TIMEOUT;
    }

    user_reaction_time++;
    return MEASURING;
}