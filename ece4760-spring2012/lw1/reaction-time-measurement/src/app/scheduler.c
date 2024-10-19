#include <avr/interrupt.h>
#include <stdbool.h>
#include "metrics.h"
#include "events.h"
#include "task/button_handler.h"
#include "task/lcd_renderer.h"
#include "task/state_resolver.h"

#define TASK_TIME_BUTTON_HANDLING           (150)
#define TASK_TIME_LCD_RENDERING             (10)
#define TASK_TIME_SYSTEM_STATE_RESOLVING    (10)
#define FAST_TRACK_TASK_TIME                (1)

static volatile uint8_t task_time_button_handling = TASK_TIME_BUTTON_HANDLING;
static volatile uint8_t task_time_lcd_rendering = TASK_TIME_LCD_RENDERING;
static volatile uint8_t task_time_system_state_resolving = TASK_TIME_SYSTEM_STATE_RESOLVING;

ISR (TIMER0_COMPA_vect)
{
    mcu_operating_time++;
    if (task_time_button_handling           > 0)    --task_time_button_handling;
    if (task_time_lcd_rendering             > 0)    --task_time_lcd_rendering;
    if (task_time_system_state_resolving    > 0)    --task_time_system_state_resolving;
}

void launch_scheduler(void)
{
    while (true)
    {
        if (task_time_button_handling == 0)         
        {
            task_time_button_handling = fast_track_mode 
                ? FAST_TRACK_TASK_TIME 
                : TASK_TIME_BUTTON_HANDLING;
            handle_button();
        }

        if (task_time_lcd_rendering == 0)
        {
            task_time_lcd_rendering = TASK_TIME_LCD_RENDERING;
            render_lcd();
        }

        if (task_time_system_state_resolving == 0)
        {
            task_time_system_state_resolving = fast_track_mode 
                ? FAST_TRACK_TASK_TIME 
                : TASK_TIME_SYSTEM_STATE_RESOLVING;
            resolve_state();
        }
    }   
}