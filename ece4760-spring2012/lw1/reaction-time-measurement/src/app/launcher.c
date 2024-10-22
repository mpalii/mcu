#include <avr/interrupt.h>
#include "drivers/gpio.h"
#include "drivers/uart.h"
#include "drivers/led.h"
#include "drivers/button.h"
#include "drivers/reset.h"
#include "drivers/lcd.h"
#include "drivers/system_timer.h"
#include "drivers/buzzer.h"
#include "messages.h"
#include "metrics.h"
#include "scheduler.h"

static inline void init_system(void);
static inline void start_system(void);

void launch_system(void)
{
    init_system();
    start_system();
}

static inline void init_system(void)
{
    // Init drivers
    init_gpio();
    init_uart();
    init_led();
    init_button();
    init_reset();
    init_lcd();
    init_system_timer();
    init_buzzer();

    // Init metrics/statistics and messages
    init_metrics();
    init_messages();
}

static inline void start_system(void)
{
    sei();                  // Enable global interrupts
    system_timer_start();   // Start system timer
    launch_scheduler();     // Jump to the super-loop
}
