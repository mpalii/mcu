#include <stdint.h>
#include "system/events.h"
#include "system/state_machine.h"

#define REPEAT_NUMBER   (8)

static int8_t repeat_number = REPEAT_NUMBER;

e_state handle_after_fast_mode_state(void)
{
    if (repeat_number > 0)
    {
        repeat_number--;
        return AFTER_FAST_MODE;
    }

    button_event = false;
    repeat_number = REPEAT_NUMBER;
    return PRE_READY;
}