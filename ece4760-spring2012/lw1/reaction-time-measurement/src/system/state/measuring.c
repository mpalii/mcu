#include <avr/interrupt.h>
#include <stdio.h>
#include "drivers/gpio.h"
#include "drivers/buzzer.h"
#include "drivers/eeprom.h"
#include "drivers/led.h"
#include "drivers/system_timer.h"
#include "drivers/reaction_timer.h"
#include "system/events.h"
#include "system/messages.h"
#include "system/metrics.h"
#include "system/state_machine.h"

volatile bool timeout = false;

ISR (TIMER1_COMPA_vect)
{
    timeout = true;
}

e_state handle_measuring_state(void)
{
    system_timer_stop();
    led_on();
    buzzer_on();
    reaction_timer_start();

    while (!timeout && (_gpio_get_input(BUTTON)));

    user_reaction_time = reaction_timer_stop();
    system_timer_start();

    fast_track_mode = false;      
    led_off();
    buzzer_off();

    if (timeout)
    {
        timeout = false;
        sprintf(text_buffer_serial, serial_pattern_timeout);
        sprintf(text_buffer_lcd, lcd_pattern_timeout);

        return PRE_READY; // NO NEED for stabilization
    }

    if (user_reaction_time < high_score)
    {
        high_score = user_reaction_time;
        eeprom_save_score(high_score);
    }

    uint16_t user_reaction_time_ms = (((uint32_t) user_reaction_time) * 16) / 1000;
    uint16_t user_reaction_time_us = (((uint32_t) user_reaction_time) * 16) % 1000;
    sprintf(text_buffer_lcd, lcd_pattern_result, user_reaction_time_ms, user_reaction_time_us);
    sprintf(text_buffer_serial, serial_pattern_result, user_reaction_time);

    return AFTER_FAST_MODE;
}