#include "system/events.h"
#include "system/state_machine.h"

e_state handle_ready_state(void)
{
    if (button_event)
    {
        button_event = false;
        return BEFORE_FAST_MODE;
    }

    return READY;
}