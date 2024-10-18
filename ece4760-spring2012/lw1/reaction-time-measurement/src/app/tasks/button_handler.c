#include "../../drivers/button.h"
#include <stdbool.h>

static enum button_state previous_state = RELEASED;
static bool event = false;

void handle_button(void)
{    
    enum button_state current_state = button_state_get();

    if (previous_state == PRE_PUSHED && current_state == PUSHED)
    {
        event = true;
    }

    previous_state = current_state;
}

bool get_button_event(void)
{
    bool result = event;
    event = false;
    return result;
}