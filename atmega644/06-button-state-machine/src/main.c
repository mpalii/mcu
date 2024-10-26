/**
 * @author Maksym Palii
 * @brief 644 gpio driver test
 * @version 1.0
 * @date 2024 August 13
 */

#define F_CPU (18432000UL)
 
#include "drivers/gpio.h"   
#include "drivers/button.h"
#include <avr/interrupt.h> 
#include <stdbool.h>
#include <stdint.h>

void init_io_pins(void);
void init_tasks(void);
void init_timer0(void);

// Task 1
#define T1 15
void task_1(void);
volatile uint8_t time1;


ISR (TIMER0_COMPA_vect)
{    
    // Adjust task's timers
    if (time1 > 0) --time1;
}


void init_tasks(void)
{
    time1 = T1;
}

int main(void) 
{
    init_gpio();
    init_timer0();
    sei();

    while (true)
    {
        if (time1 == 0) task_1();
    }
}   

/****************************************************************************/
/* Set up timer 0 for 1 ms timebase                                         */
/* (1024 (prescaler) * 18 (OCR0A + 1)) / 18_432_000 MHz = 0.001s = 1ms      */
/****************************************************************************/
void init_timer0(void)
{
    // TCCR0A - Timer/Counter0 Control Register channel A
    TCCR0A = _BV(WGM01);            // Clear Timer on Compare Match (CTC) mode (only works with channel)

    // TCCR0B - Timer/Counter0 Control Register channel B
    TCCR0B = _BV(CS02) | _BV(CS00); // clk/1024 (From prescaler)

    // OCR0A - Timer/Counter0 Output Compare Register channel A
    OCR0A =	17;                     //set the compare reg to 18 time ticks (zero based)

    // TIMSK0 - Timer/Counter0 Interrupt Mask Register
    TIMSK0 = _BV(OCIE0A);           // Timer/Counter0 Output Compare Match channel A Interrupt Enable
}

/****************************************************************************/
/* Tasks implementation section                                             */
/****************************************************************************/

enum button_state previous_state = RELEASED;

void task_1(void)
{
    // re-initialize task 1 timer
    time1 = T1;

    enum button_state current_state = button_state_get();

    if (previous_state == PRE_PUSHED && current_state == PUSHED)
    {
        GPIO_TOGGLE(LED);
    }

    previous_state = current_state;
}
