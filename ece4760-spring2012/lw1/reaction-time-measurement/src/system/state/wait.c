#include <stdio.h>
#include "drivers/buzzer.h"
#include "drivers/lcd.h"
#include "drivers/led.h"
#include "system/events.h"
#include "system/messages.h"
#include "system/metrics.h"
#include "system/state_machine.h"

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
        buzzer_on();
        return MEASURING;
    }

    delay--;
    return WAIT;
}