#include <avr/interrupt.h>
#include <stdbool.h>
#include "metrics.h"
#include "events.h"
#include "task/button_handler.h"
#include "task/lcd_renderer.h"
#include "task/state_resolver.h"
#include "task/serial_writer.h"

#define TASK_TIME_BUTTON_HANDLING           (255)
#define TASK_TIME_LCD_RENDERING             (10)
#define TASK_TIME_SYSTEM_STATE_RESOLVING    (1)
#define TASK_TIME_SERIAL_WRITING            (1)

static volatile uint8_t task_time_button_handling = TASK_TIME_BUTTON_HANDLING;
static volatile uint8_t task_time_lcd_rendering = TASK_TIME_LCD_RENDERING;
static volatile uint8_t task_time_system_state_resolving = TASK_TIME_SYSTEM_STATE_RESOLVING;
static volatile uint8_t task_time_serial_writing = TASK_TIME_SERIAL_WRITING;

ISR (TIMER0_COMPA_vect)
{
    mcu_operating_time++;
    if (task_time_button_handling           > 0)    --task_time_button_handling;
    if (task_time_lcd_rendering             > 0)    --task_time_lcd_rendering;
    if (task_time_system_state_resolving    > 0)    --task_time_system_state_resolving;
    if (task_time_serial_writing            > 0)    --task_time_serial_writing;
}

void launch_scheduler(void)
{
    // MAIN super-loop
    while (true)
    {
        if (task_time_button_handling == 0)         
        {
            task_time_button_handling = fast_track_mode ? 1 : TASK_TIME_BUTTON_HANDLING;
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

        if (task_time_serial_writing == 0)
        {
            task_time_serial_writing = TASK_TIME_SERIAL_WRITING;
            serial_write();
        }
    }   
}