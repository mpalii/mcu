/**
 * @author Maksym Palii
 * @brief Task manager
 * @version 2.0
*/

#include "task_manager.h"

void init_timer_0(void);

// Global time
volatile uint32_t system_time = 0;

// Task 1
#define T1 1
void task_1(void);
volatile uint8_t time1;

// Task 2
#define T2 250
void task_2(void);
volatile uint8_t time2;

ISR (TIMER0_COMPA_vect)
{    
    // Increment global time
    system_time++;

    // Adjust task's timers
    if (time1 > 0) --time1;
    if (time2 > 0) --time2;
}

void init_tasks(void)
{
    time1 = T1;
    time2 = T2;
}

void handle_tasks(void) {
    if (time1 == 0) task_1();
    if (time2 == 0) task_2();
}

/****************************************************************************/
/* Tasks implementation section                                             */
/****************************************************************************/

void task_1(void)
{
    // re-initialize task 1 timer
    time1 = T1;
    // Render cx56 buffer
    cx56_render();
}

void task_2(void)
{
    // re-initialize task 2 timer
    time2 = T2;
    // Pass sADC conversion result to split function
    cx56_split(adc_get_conversion_result());
}
