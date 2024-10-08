//Run all three timers in different modes
// timer 0 -- compare-match timebase
// timer 1 -- input capture from analog comparator
// timer 2 -- stand alone square wave gen  

// task 1 will  print the periods 
// timer0 compare ISR will increment a timer
// timer1 capture ISR will compute a period from the capture

// Connect port B.0 (ICP1) to port B.3 (OC2A)

#define F_CPU 8000000UL
                
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "uart328p.h"

static inline void init_io_pins(void);
static inline void init_tasks(void);
static inline void init_timer_0(void);
static inline void init_timer_1(void);
static inline void init_timer_2(void);

// Task 1
#define T1 250
void task_1(void);
volatile uint8_t time1;

// timer 1 capture variables for computing sq wave period	
volatile unsigned int T1capture, lastT1capture, period ; 
         
ISR (TIMER0_COMPA_vect) 
{    
    if (time1 > 0) --time1;
}

ISR (TIMER1_CAPT_vect)
{
    // read timer1 input capture register
    T1capture = ICR1 ; 
    // compute time between captures
    period =  T1capture - lastT1capture;
    lastT1capture = T1capture ;
}

//**********************************************************       
//Entry point and task scheduler loop
int main(void)
{  
    init_io_pins();
    init_tasks();
    init_timer_0();
    init_timer_1();
    init_timer_2();
    stdin = stdout = stderr = uart_init(F_CPU, 9600, false);
    sei();

    fprintf(stdout,"Start up...\r\n");
  
    while(true)
    {  
        if (time1 == 0) task_1();
    }
}

static inline void init_io_pins(void)
{
    DDRB |= _BV(PB3);
}

static inline void init_tasks(void)
{
    time1 = T1;
}

/****************************************************************************/
/* Set up timer 0 for 1 mSec timebase                                       */
/* (64 (prescaler) * 125 (OCR0A + 1)) / 8_000_000 MHz = 0.001Sec = 1mSec    */
/****************************************************************************/
static inline void init_timer_0(void)
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
/* Set up timer 1 for Input Capture mode                                    */
/* Capture rising edge, no prescaling, interrupt based                      */
/****************************************************************************/
static inline void init_timer_1(void)
{   
    //  TCCR1B – Timer/Counter1 Control Register channel B
    TCCR1B = _BV(ICES1) | _BV(CS10); // set capture to positive edge, full counting rate
    // TIMSK1 – Timer/Counter1 Interrupt Mask Register
    TIMSK1 = _BV(ICIE1) ;            // Timer/Counter1 Input Capture Interrupt Enable
}

/****************************************************************************/
/* Set up timer 2 for 880Hz frequency                                       */
/* (32 (prescaler) * 142 (OCR2A + 1) * 2) / 8_000_000 MHz = 0.001136Sec     */
/****************************************************************************/
static inline void init_timer_2(void)
{	
    // TCCR2A – Timer/Counter2 Control Register channel A
    TCCR2A = _BV(COM2A0) | _BV(WGM21);   
	
    // TCCR2B – Timer/Counter0 Control Register channel B
    TCCR2B = _BV(CS21) | _BV(CS20);    // clkT2 S/32
	
    // OCR2A – Timer/Counter0 Output Compare Register channel A
    OCR2A = 141;			   //set the compare reg to 142 ticks (zero based)
}
  
/****************************************************************************/
/* Tasks implementation section                                             */
/****************************************************************************/
void task_1(void) 
{  
    // re-initialize task 1 timer
    time1 = T1;

    // print capture interval 
    fprintf(stdout,"%d\r\n", period);
}
 