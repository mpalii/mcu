#include "app/state_machine.h"
#include "app/events.h"

e_state handle_ready_state(void)
{
    if (button_event)
    {
        button_event = false;
        return BEFORE_FAST_MODE;
    }

    return READY;
}