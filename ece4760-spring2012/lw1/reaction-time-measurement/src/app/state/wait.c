#include <stdio.h>
#include "app/state_machine.h"
#include "app/messages.h"
#include "app/metrics.h"
#include "app/events.h"
#include "drivers/lcd.h"
#include "drivers/led.h"
#include "drivers/timer2.h"

e_state handle_wait_state(void)
{
    if (button_event)
    {
        button_event = false;
        fast_track_mode = false;

        sprintf(text_buffer_serial, FALSE_START_SERIAL_PATTERN, (mcu_operating_time / 10));
        sprintf(text_buffer_lcd, FALSE_START_LCD_MESSAGE);

        return AFTER_FAST_MODE;     // stabilization needs
    }

    if (delay == 0)
    {
        led_on();
        timer2_start();
        return PRE_MEASURING;
    }

    delay--;
    return WAIT;
}