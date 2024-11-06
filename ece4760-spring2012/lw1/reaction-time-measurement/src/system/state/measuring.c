#include <avr/interrupt.h>
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
        text_buffer_serial = serial_pattern_timeout;
        text_buffer_lcd = lcd_pattern_timeout;

        return PRE_READY; // NO NEED for stabilization
    }

    if (user_reaction_time < high_score)
    {
        high_score = user_reaction_time;
        eeprom_save_score(high_score);
    }

    text_buffer_serial = serial_pattern_result;
    text_buffer_lcd = get_lcd_result_message();

    return AFTER_FAST_MODE;

    


    // if (button_event)
    // {
    //     button_event = false;
    //     fast_track_mode = false;      

    //     led_off();
    //     buzzer_off();

    //     if (user_reaction_time > 0)
    //     {
    //         // this is an attempt to reduce the error of measurement
    //         // in fact thid delay can take up to 0.2ms
    //         // but reduce the user reaction time per 0.1ms will be enough
    //         user_reaction_time--;
    //     }

    //     if (user_reaction_time < high_score)
    //     {
    //         high_score = user_reaction_time;
    //         eeprom_save_score(high_score);
    //     }

    //     text_buffer_serial = serial_pattern_result;
    //     text_buffer_lcd = get_lcd_result_message();

    //     return AFTER_FAST_MODE;
    // }

    // if (user_reaction_time == 10000)
    // {
    //     fast_track_mode = false;
    //     led_off();
    //     buzzer_off();

    //     text_buffer_serial = serial_pattern_timeout;
    //     text_buffer_lcd = lcd_pattern_timeout;

    //     return PRE_READY; // NO NEED for stabilization
    // }

    // user_reaction_time++;
    // return MEASURING;
}