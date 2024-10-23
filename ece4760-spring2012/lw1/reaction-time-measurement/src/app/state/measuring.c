#include <stdio.h>
#include "app/state_machine.h"
#include "app/messages.h"
#include <app/metrics.h>
#include <app/events.h>
#include "drivers/led.h"
#include "drivers/buzzer.h"
#include "drivers/eeprom.h"

e_state handle_measuring_state(void)
{
    if (button_event)
    {
        button_event = false;
        fast_track_mode = false;      

        led_off();
        buzzer_off();

        if (user_reaction_time < high_score)
        {
            high_score = user_reaction_time;
            eeprom_save_score(high_score);
        }

        sprintf(text_buffer_serial, RESULT_SERIAL_PATTERN, (mcu_operating_time / 10), (user_reaction_time / 10), (user_reaction_time % 10));
        sprintf(text_buffer_lcd, RESULT_LCD_PATTERN, (user_reaction_time / 10), (user_reaction_time % 10));

        return AFTER_FAST_MODE;
    }

    if (user_reaction_time == 10000)
    {
        fast_track_mode = false;
        led_off();
        buzzer_off();

        sprintf(text_buffer_serial, TIMEOUT_SERIAL_PATTERN, (mcu_operating_time / 10));
        sprintf(text_buffer_lcd, TIMEOUT_LCD_MESSAGE);

        return PRE_READY; // NO NEED for stabilization
    }

    user_reaction_time++;
    return MEASURING;
}