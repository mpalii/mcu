#include "system/state_machine.h"
#include "system/state/vcc_measuring.h"
#include "system/state/res_measuring_1k.h"
#include "system/state/res_measuring_10k.h"
#include "system/state/res_measuring_100k.h"

static e_state state = VCC_MEASURING;

e_state (*handle_state[])(void) = 
{
    handle_vcc_measuring,
    handle_res_1k_measuring,
    handle_res_10k_measuring,
    handle_res_100k_measuring
};

void handle_device_state(void)
{
    state = handle_state[state]();
}

e_state get_device_state(void)
{
    return state;
}