#include <stdint.h>
#include "system/events.h"
#include "system/state_machine.h"
#include "system/metrics.h"
#include <stdlib.h>

#define REPEAT_NUMBER   (20)

static int8_t repeat_number = REPEAT_NUMBER;

e_state handle_before_fast_mode_state(void)
{
    if (repeat_number > 0)
    {
        repeat_number--;
        return BEFORE_FAST_MODE;
    }

    srand((unsigned int) mcu_operating_time);
    delay = 10000 + (rand() % 55535);
    fast_track_mode = true;
    user_reaction_time = 0;

    button_event = false;
    repeat_number = REPEAT_NUMBER;
    return PRE_WAIT;
}