/**
 * @author Maksym Palii
 * @brief Shift-register SN74HC595 driver 
 * @version 1.0
*/

#include "sn74hc595.h"
#include "gpio.h"

int8_t column_index = -1;

void shift_column(void)
{
    // overflow check
    if (++column_index > 63)
    {
        column_index = 0;
    }

    
    for (uint8_t i = 0; i < 64; i++)
    {
        GPIO_LOW(SRCLK);

        if (column_index == i)
        {
            GPIO_LOW(SER);
        }
        else
        {
            GPIO_HIGH(SER);
        }

        GPIO_HIGH(SRCLK);
    }

    GPIO_LOW(SRCLK);

    GPIO_HIGH(RCLK);
    GPIO_LOW(RCLK);
}