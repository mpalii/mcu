#include <stdbool.h>
#include "drivers/button.h"
#include "system/events.h"

static enum button_state previous_state = RELEASED;

void handle_button(void)
{
    enum button_state current_state = button_state_get();

    if (previous_state == PRE_PUSHED && current_state == PUSHED)
    {
        button_event = true;
    }

    previous_state = current_state;
}