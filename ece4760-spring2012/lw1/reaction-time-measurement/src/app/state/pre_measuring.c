#include <stdio.h>
#include "drivers/uart.h"
#include "app/messages.h"
#include "app/metrics.h"
#include "app/state_machine.h"

e_state handle_pre_measuring_state(void)
{
    sprintf(text_buffer_serial, MEASURING_SERIAL_PATTERN, (mcu_operating_time / 10));
    uart_add_to_buffer(text_buffer_serial);

    return MEASURING;
}
