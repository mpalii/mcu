#include "state_machine.h"
#include "state/pre_ready.h"
#include "state/ready.h"
#include "state/pre_wait.h"
#include "state/wait.h"
#include "state/measuring.h"
#include "state/result.h"
#include "state/false_start.h"
#include "state/timeout.h"

static e_state next_state = PRE_READY;

e_state (*handle_state[])(void) = 
{
    handle_pre_ready_state,
    handle_ready_state,
    handle_pre_wait_state,
    handle_wait_state,
    handle_measuring_state,
    handle_result_state,
    handle_false_start_state,
    handle_timeout_state
};

void handle_device_state(void)
{
    next_state = handle_state[next_state]();
}