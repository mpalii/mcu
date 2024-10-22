#include "app/state_machine.h"
#include "app/events.h"
#include <stdint.h>

#define REPEAT_NUMBER   (20)

static int8_t repeat_number = REPEAT_NUMBER;

e_state handle_before_fast_mode_state(void)
{
    if (repeat_number > 0)
    {
        repeat_number--;
        return BEFORE_FAST_MODE;
    }

    button_event = false;
    repeat_number = REPEAT_NUMBER;
    return PRE_WAIT;
}