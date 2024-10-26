#include "button.h"
#include "gpio.h"
#include <stdbool.h>

static enum button_state state;

enum button_state button_state_get(void)
{
    bool push_probe = (GPIO_GET_INPUT(BUTTON) == 0);

    switch (state)
    {
        case RELEASED:
            state = push_probe ? PRE_PUSHED : RELEASED;
            break;
        
        case PRE_PUSHED:
            state = push_probe ? PUSHED : RELEASED;
            break;
        
        case PUSHED:
            state = push_probe ? PUSHED : PRE_RELEASED;
            break;
        
        case PRE_RELEASED:
            state = push_probe ? PUSHED : RELEASED;
            break;
    }

    return state;
}