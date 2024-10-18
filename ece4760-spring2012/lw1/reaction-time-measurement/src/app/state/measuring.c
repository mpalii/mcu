#include "../state_machine.h"
#include "../tasks/button_handler.h"
#include "../../drivers/led.h"
#include "../../drivers/uart.h"
#include "../../drivers/lcd.h"
#include "../../drivers/timer1.h"
#include "../../drivers/timer2.h"
#include "../../app/metrics.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <avr/interrupt.h>

typedef enum
{
    INITIALIZATION,
    DELAY,
    MEASUREMENT,
    EXIT
} measuring_substate;

volatile static measuring_substate substate = INITIALIZATION;
volatile static e_state exit_status;
static uint16_t delay_time;
static uint16_t timeout;

static void process_init(void)
{
    srand((unsigned int) get_system_time());
    delay_time = 999 + (rand() % 9000);
    uart_transmit("WAIT\r\n");
    lcd_add_to_rendering("WAIT************");
    substate = DELAY;
}

static void process_delay(void)
{
    if (delay_time == 980)
    {
        // enable external interrupt
        EIMSK |= _BV(INT0);
    }

    if (delay_time == 0)
    {
        substate = MEASUREMENT;
        timeout = 1000;
        // enable LED and buzzer
        led_on();
        timer2_start();
        timer1_start();
    }
    else delay_time--;
}

static void process_measure(void)
{
    if (timeout == 0)
    {   
        // disable external interrupt
        EIMSK &= ~_BV(INT0);
        // disable LED and buzzer
        led_off();
        timer2_stop();

        substate = EXIT;
        exit_status = TIMEOUT;
    }
    else timeout--;
}

e_state handle_measuring_state(void)
{
    switch (substate)
    {
        case INITIALIZATION:
            process_init();
            break;
        case DELAY:
            process_delay();
            break;
        case MEASUREMENT:
            process_measure();
            break;
        case EXIT:
            substate = INITIALIZATION;
            get_button_event(); // just to reset event
            return exit_status;
    }

    return MEASURING;
}

ISR (INT0_vect)
{
    uint16_t timer1_time = timer1_stop();

    // disable LED and buzzer
    led_off();
    timer2_stop();

    // disable external interrupt
    EIMSK &= ~_BV(INT0);

    if (substate == DELAY)
    {
        exit_status = TIMEOUT;
    }

    if (substate == MEASUREMENT)
    {
        set_reaction_time(timer1_time);
        exit_status = RESULT;
    }

    substate = EXIT;
}