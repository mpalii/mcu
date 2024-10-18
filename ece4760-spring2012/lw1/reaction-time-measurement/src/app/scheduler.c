#include <avr/interrupt.h>
#include <stdbool.h>
#include "metrics.h"
#include "tasks/button_handler.h"
#include "tasks/lcd_renderer.h"
#include "tasks/state_resolver.h"

#define TASK_TIME_BUTTON_HANDLING           (15)
#define TASK_TIME_LCD_RENDERING             (1)
#define TASK_TIME_SYSTEM_STATE_RESOLVING    (1)

volatile uint8_t task_time_button_handling = TASK_TIME_BUTTON_HANDLING;
volatile uint8_t task_time_lcd_rendering = TASK_TIME_LCD_RENDERING;
volatile uint8_t task_time_system_state_resolving = TASK_TIME_SYSTEM_STATE_RESOLVING;

ISR (TIMER0_COMPA_vect)
{
    increment_system_time();
    if (task_time_button_handling           > 0)    --task_time_button_handling;
    if (task_time_lcd_rendering             > 0)    --task_time_lcd_rendering;
    if (task_time_system_state_resolving    > 0)    --task_time_system_state_resolving;
}

// void init_scheduler(void)
// {
//     task_time_button_handling = TASK_TIME_BUTTON_HANDLING;
//     task_time_lcd_rendering = TASK_TIME_LCD_RENDERING;
//     task_time_system_state_resolving = TASK_TIME_SYSTEM_STATE_RESOLVING;
// }

void scheduler_launch(void)
{
    while (true)
    {
        if (task_time_button_handling == 0)         
        {
            task_time_button_handling = TASK_TIME_BUTTON_HANDLING;
            handle_button();
        }

        if (task_time_lcd_rendering == 0)
        {
            task_time_lcd_rendering = TASK_TIME_LCD_RENDERING;
            render_lcd();
        }

        if (task_time_system_state_resolving == 0)
        {
            task_time_system_state_resolving = TASK_TIME_SYSTEM_STATE_RESOLVING;
            resolve_state();
        }
    }   
}