#include <avr/interrupt.h>
#include "drivers/gpio.h"
#include "drivers/uart.h"
#include "drivers/led.h"
#include "drivers/button.h"
#include "drivers/reset.h"
#include "drivers/lcd.h"
#include "drivers/timer2.h"
#include "drivers/timer0.h"
#include "metrics.h"
#include "scheduler.h"

static inline void init_system(void);
static inline void start_system(void);

void launch_app(void)
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
    init_timer2();
    init_timer0();

    // Init metrics and statistics
    init_metrics();
}

static inline void start_system(void)
{
    sei();                  // Enable global interrupts
    timer0_start();         // Start system timer
    launch_scheduler();     // Jump to the super-loop
}
