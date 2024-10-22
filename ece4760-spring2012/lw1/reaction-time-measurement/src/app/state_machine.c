#include "state_machine.h"
#include "state/pre_ready.h"
#include "state/ready.h"
#include "state/before_fast_mode.h"
#include "state/pre_wait.h"
#include "state/wait.h"
#include "state/pre_measuring.h"
#include "state/measuring.h"
#include "state/after_fast_mode.h"

static e_state next_state = PRE_READY;

e_state (*handle_state[])(void) = 
{
    handle_pre_ready_state,
    handle_ready_state,
    handle_before_fast_mode_state,
    handle_pre_wait_state,
    handle_wait_state,
    handle_pre_measuring_state,
    handle_measuring_state,
    handle_after_fast_mode_state
};

void handle_device_state(void)
{
    next_state = handle_state[next_state]();
}