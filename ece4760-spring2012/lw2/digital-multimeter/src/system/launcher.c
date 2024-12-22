#include <avr/interrupt.h>
#include "drivers/gpio.h"
#include "drivers/lcd.h"
#include "drivers/adc.h"
#include "drivers/timer_0.h"
#include "drivers/button.h"
#include "system/scheduler.h"

static inline void init_drivers(void);
static inline void start_system(void);

void launch_system(void)
{
    init_drivers();
    start_system();
}

static inline void init_drivers(void)
{
    init_gpio();
    init_lcd();
    init_adc();
    init_timer_0();
    init_button();
}

static inline void start_system(void)
{
    sei();                  // Enable global interrupts
    timer_0_start();        // Start system timer
    launch_scheduler();     // Jump to the super-loop
}
