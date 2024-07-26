/**
 * @author Maksym Palii
 * @brief Encoder (external interrupt driven) and LCD1602
 * @version 1.0
 * @date 2024 July 21
 */

#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "drivers/gpio.h"
#include "drivers/lcd1602.h"
#include "drivers/timer0.h"

char buffer[16];

int16_t duty = 128;

ISR (INT0_vect)
{    
    // handle encoder change
    if (GPIO_GET_INPUT(ENCODER_2ND))
    {
        duty--;
    }
    else 
    {
        duty++;
    }

    if (duty < 0) duty = 0;
    if (duty > 255) duty = 255;
}


int main(void)
{
    init_gpio();
    init_lcd1602();
    // init_timer0();

    // EICRA |= _BV(ISC01) | _BV(ISC00);
    EICRA |= _BV(ISC01);
    EIMSK |= _BV(INT0);

    sei();
	
    while (true)
    {
        // render value
        memset(buffer, '\0', sizeof(buffer));
        send_command(0xC0);
        sprintf(buffer, "%3d", duty);
        print(buffer);
    }
}
