/**
 * @author Maksym Palii
 * @brief 644 Timer 0, fast PWM mode
 * @version 1.0
 * @date 2024 September 05
 */
 
#define F_CPU      (16000000UL)

#include <util/delay.h>
#include "drivers/gpio.h"   
#include "drivers/timer0.h" 

int main(void) 
{
    init_gpio();
    init_timer0();

    set_duty(127);
    // set_duty(255);

    while (true)
    {
        // for (uint8_t duty = 0; duty < 255; duty++)
        // {
        //     set_duty(duty);
        //     _delay_ms(20);
        // }
        // _delay_ms(1000);

        // for (uint8_t duty = 255; duty > 0; duty--)
        // {
        //     set_duty(duty);
        //     _delay_ms(20);
        // }
        // _delay_ms(1000);
    }
}   
  