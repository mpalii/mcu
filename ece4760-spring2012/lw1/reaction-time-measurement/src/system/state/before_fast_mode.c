#include <stdint.h>
#include <stdlib.h>
#include "system/events.h"
#include "system/state_machine.h"
#include "system/metrics.h"

#define REPEAT_NUMBER   (200)

static int8_t repeat_number = REPEAT_NUMBER;

e_state handle_before_fast_mode_state(void)
{
    if (repeat_number > 0)
    {
        repeat_number--;
        return BEFORE_FAST_MODE;
    }

    srand((unsigned int) random_seed);
    delay = 1535 + (rand() % 64000);
    fast_track_mode = true;
    user_reaction_time = 0;

    button_event = false;
    repeat_number = REPEAT_NUMBER;
    return PRE_WAIT;
}