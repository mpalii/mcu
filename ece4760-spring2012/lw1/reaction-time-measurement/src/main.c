/**
 * @author Maksym Palii
 * @brief Reaction time measurement
 * @version 1.0
 * @date 2024 October 13
 * @link https://people.ece.cornell.edu/land/courses/ece4760/labs/s2012/lab1.html
 */

#define F_CPU (16000000UL)
 
#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>

int main(void) 
{
    DDRA |= _BV(PA0);

    while (true)
    {
        PORTA ^= _BV(PA0);
        _delay_ms(500);
    }
}   
  