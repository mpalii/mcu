#include "system/state_machine.h"
#include "system/state/pre_ready.h"
#include "system/state/ready.h"
#include "system/state/before_fast_mode.h"
#include "system/state/pre_wait.h"
#include "system/state/wait.h"
#include "system/state/measuring.h"
#include "system/state/after_fast_mode.h"

static e_state next_state = PRE_READY;

e_state (*handle_state[])(void) = 
{
    handle_pre_ready_state,
    handle_ready_state,
    handle_before_fast_mode_state,
    handle_pre_wait_state,
    handle_wait_state,
    handle_measuring_state,
    handle_after_fast_mode_state
};

void handle_device_state(void)
{
    next_state = handle_state[next_state]();
}