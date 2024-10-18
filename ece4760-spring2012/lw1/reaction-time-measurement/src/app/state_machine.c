#include "state_machine.h"
#include "state/ready.h"
#include "state/measuring.h"
#include "state/result.h"
#include "state/false_start.h"
#include "state/timeout.h"

static e_state device_state = READY;

e_state (*handle_state[])(void) = 
{
    handle_ready_state,
    handle_measuring_state,
    handle_result_state,
    handle_false_start_state,
    handle_timeout_state
};

void handle_device_state(void)
{
    device_state = handle_state[device_state]();
}