#include <avr/interrupt.h>
#include <stdbool.h>
#include "drivers/gpio.h"
#include "system/state_machine.h"
#include "system/task/button_handler.h"
#include "system/task/lcd_renderer.h"
#include "system/task/state_resolver.h"

#define TASK_TIME_LCD_RENDERING             (1)
#define TASK_TIME_SYSTEM_STATE_RESOLVING    (40)
#define TASK_TIME_BUTTON_HANDLING           (40)

static volatile uint8_t task_time_lcd_rendering = TASK_TIME_LCD_RENDERING;
static volatile uint8_t task_time_system_state_resolving = TASK_TIME_SYSTEM_STATE_RESOLVING;
static volatile uint8_t task_time_button_handling = TASK_TIME_BUTTON_HANDLING;

ISR (TIMER0_COMPA_vect)
{
    if (task_time_lcd_rendering             > 0)    --task_time_lcd_rendering;
    if (task_time_system_state_resolving    > 0)    --task_time_system_state_resolving;
    if (task_time_button_handling           > 0)    --task_time_button_handling;
}

void launch_scheduler(void)
{
    // MAIN super-loop
    while (true)
    {
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
        
        if (task_time_button_handling == 0)         
        {
            task_time_button_handling = TASK_TIME_BUTTON_HANDLING;
            handle_button();
        }
    }   
}