#include <avr/interrupt.h>
#include <stdbool.h>
#include "drivers/gpio.h"
#include "system/events.h"
#include "system/metrics.h"
#include "system/state_machine.h"
#include "system/task/button_handler.h"
#include "system/task/lcd_renderer.h"
#include "system/task/state_resolver.h"
#include "system/task/serial_writer.h"
#include "system/task/eeprom_writer.h"
#include "system/task/serial_input_handler.h"

#define TASK_TIME_BUTTON_HANDLING           (150)
#define TASK_TIME_LCD_RENDERING             (10)
#define TASK_TIME_SYSTEM_STATE_RESOLVING    (100)
#define TASK_TIME_SERIAL_WRITING            (1)
#define TASK_TIME_EEPROM_WRITING            (1)
#define TASK_TIME_SERIAL_READING            (1)

static volatile uint8_t task_time_button_handling = TASK_TIME_BUTTON_HANDLING;
static volatile uint8_t task_time_lcd_rendering = TASK_TIME_LCD_RENDERING;
static volatile uint8_t task_time_system_state_resolving = TASK_TIME_SYSTEM_STATE_RESOLVING;
static volatile uint8_t task_time_serial_writing = TASK_TIME_SERIAL_WRITING;
static volatile uint8_t task_time_eeprom_writing = TASK_TIME_EEPROM_WRITING;
static volatile uint8_t task_time_serial_reading = TASK_TIME_SERIAL_READING;

ISR (TIMER0_COMPA_vect)
{
    mcu_operating_time++;
    if (task_time_button_handling           > 0)    --task_time_button_handling;
    else _gpio_high(DEADLINE_IND);
    if (task_time_lcd_rendering             > 0)    --task_time_lcd_rendering;
    else _gpio_high(DEADLINE_IND);
    if (task_time_system_state_resolving    > 0)    --task_time_system_state_resolving;
    else _gpio_high(DEADLINE_IND);
    if (task_time_serial_writing            > 0)    --task_time_serial_writing;
    else _gpio_high(DEADLINE_IND);
    if (task_time_eeprom_writing            > 0)    --task_time_eeprom_writing;
    else _gpio_high(DEADLINE_IND);
    if (task_time_serial_reading            > 0)    --task_time_serial_reading;
    else _gpio_high(DEADLINE_IND);
}

void launch_scheduler(void)
{
    // MAIN super-loop
    while (true)
    {

        if (task_time_system_state_resolving == 0)
        {
            task_time_system_state_resolving = fast_track_mode ? 1 : TASK_TIME_SYSTEM_STATE_RESOLVING;
            resolve_state();
        }

        if (task_time_serial_reading == 0)
        {
            task_time_serial_reading = TASK_TIME_SERIAL_READING;
            if (get_device_state() == READY) handle_serial_input();
        }

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

        if (task_time_serial_writing == 0)
        {
            task_time_serial_writing = TASK_TIME_SERIAL_WRITING;
            serial_write();
        }

        if (task_time_eeprom_writing == 0)
        {
            task_time_eeprom_writing = TASK_TIME_EEPROM_WRITING;
            eeprom_write();
        }
    }   
}