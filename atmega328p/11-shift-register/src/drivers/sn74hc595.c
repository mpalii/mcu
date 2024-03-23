/**
 * @author Maksym Palii
 * @brief Shift-register SN74HC595 driver 
 * @version 1.0
*/

#include "sn74hc595.h"
#include "gpio.h"

void shift_data(uint16_t data)
{
    for (uint8_t i = 0; i < 16; i++)
    {
        GPIO_LOW(SRCLK);

        if (data & (1 << i))
        {
            GPIO_HIGH(SER);
        }
        else
        {
            GPIO_LOW(SER);
        }

        GPIO_HIGH(SRCLK);
    }

    GPIO_LOW(SRCLK);

    GPIO_HIGH(RCLK);
    GPIO_LOW(RCLK);
}