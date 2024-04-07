/**
 * @author Maksym Palii
 * @brief Frequency meter, external interrupt based approach
 * @version 1.0
 * @date 2024 April 07
 */

#define F_CPU (8000000UL)

#include <avr/interrupt.h>
#include <stdbool.h>
#include "drivers/cx56.h"
#include "drivers/gpio.h"

void init_tasks(void);
void init_timer_0(void);
void init_timer_1(void);
void init_external_interrupt_0(void);

// Timer 1 overflow counter
volatile uint32_t timer_1_overflow_counter = 0;

// Timer/Counter 1 value
volatile uint32_t timer_1_value = 0;

// Task 1
#define T1 2
void task_1(void);
volatile uint8_t time1;

ISR(TIMER0_COMPA_vect)
{    
    // Adjust task's timers
    if (time1 > 0) --time1;
}

ISR(INT0_vect)
{
    timer_1_value = TCNT1 + timer_1_overflow_counter * 65536;
    TCNT1 = 0;
    timer_1_overflow_counter = 0;

    // GPIO_TOGGLE(LED);
}

ISR(TIMER1_OVF_vect)
{
    timer_1_overflow_counter++;
}

int main(void)
{
    gpio_init();
    init_tasks();
    init_timer_0();
    init_timer_1();
    init_external_interrupt_0();
    sei();
	
    while (true)
    {
        if (time1 == 0) task_1();
    }
}

void init_tasks(void)
{
    time1 = T1;
}

/****************************************************************************/
/* Set up timer 0 for 1 mSec timebase                                       */
/* (64 (prescaler) * 125 (OCR0A + 1)) / 8_000_000 MHz = 0.001Sec = 1mSec    */
/****************************************************************************/
void init_timer_0(void)
{
    // TCCR0A – Timer/Counter0 Control Register channel A
    TCCR0A = _BV(WGM01);             // Clear Timer on Compare Match (CTC) mode (only works with channel)
	
    // TCCR0B – Timer/Counter0 Control Register channel B
    TCCR0B = _BV(CS01) | _BV(CS00);  // clk/64 (From prescaler)
	
    // OCR0A – Timer/Counter0 Output Compare Register channel A
    OCR0A =	124;                     //set the compare reg to 125 time ticks (zero based)
	
    // TIMSK0 – Timer/Counter0 Interrupt Mask Register
    TIMSK0 = _BV(OCIE0A);            // Timer/Counter0 Output Compare Match channel A Interrupt Enable
}

/****************************************************************************/
/* Set up timer 1 without prescaler                                         */
/****************************************************************************/
void init_timer_1(void)
{
    // TCCR1B – Timer/Counter1 Control Register channel B
    TCCR1B = _BV(CS10);     // clk I/O/1 (No prescaling)
	
    // TIMSK1 – Timer/Counter1 Interrupt Mask Register
    TIMSK1 = _BV(TOIE1);    // Timer/Counter1, Overflow Interrupt Enable
}

void init_external_interrupt_0(void)
{
    // The falling edge of INT0 generates an interrupt request
    EICRA = _BV(ISC01);

    // External Interrupt Request 0 Enable
    EIMSK = _BV(INT0);
}

/****************************************************************************/
/* Tasks implementation section                                             */
/****************************************************************************/

void task_1(void)
{
    // re-initialize task 1 timer
    time1 = T1;

    // Render frequency
    render(F_CPU/timer_1_value);
}
