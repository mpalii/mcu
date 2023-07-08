/*
 * @author Maksym Palii
 * @brief Random number generator
 * @version 1.0
 * @date 2023 July 01
 */

#define F_CPU (8000000UL)

#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>
#include "uart328p.h"

volatile uint32_t mcu_operating_time = 0;

ISR (TIMER1_COMPA_vect)
{
    mcu_operating_time++;
}

/****************************************************************************/
/* Set up timer 1 for 1 mSec timebase                                       */
/* (1 (prescaler) * 8000 (OCR0A + 1)) / 8_000_000 MHz = 0.001Sec = 1mSec    */
/****************************************************************************/
void init_timer_0(void)
{	
    // TCCR1B – Timer/Counter1 Control Register channel B
    TCCR1B = _BV(WGM12) | _BV(CS10);    // CTC mode, /clk I/O/1 (No prescaling)
	
    // OCR1A – Timer/Counter1 Output Compare Register channel A
    OCR1A = 7999;                       //set the compare reg to 80 ticks (zero based)
	
    // TIMSK1 – Timer/Counter1 Interrupt Mask Register
    TIMSK1 = _BV(OCIE1A);               // Timer/Counter0 Output Compare Match channel A Interrupt Enable
}

int main(void)
{
    char input_command[5];

    init_timer_0();
    sei();
    stdin = stdout = stderr = uart_init(F_CPU, 9600, false);

    printf("Start up...\r\n");

    while (true)
    {
        // wait for user input
        scanf("%4s", input_command);

        if (strcmp(input_command, "rnd") == 0)
        {
            uint32_t timestamp = mcu_operating_time;
            printf("Time: %lums - ", timestamp);

            unsigned int seed = (unsigned int) timestamp;
            srand(seed);
            printf("Seed: %u - ", seed);

            for (uint8_t i = 0; i < 5; i++)
            {
                printf("%d ", rand());
            }
            printf("\r\n");
        }
        else
        {
            printf("UNKNOWN\r\n");
        }
    }
}
