/*
 * @author Maksym Palii
 * @brief SIN lookup table (full period)
 * @version 1.0
 * @date 2024 September 07
 */

#define F_CPU               (18432000UL)
#define BAUD_RATE           (9600UL)
#define SIN_LUT_SIZE        (256)

#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "drivers/gpio.h"
#include "drivers/uart.h"

int main(void)
{
    init_gpio();
    init_uart(F_CPU, BAUD_RATE, false);

    printf("const int8_t sin_table[256] =\r\n{");
    for (uint16_t i = 0; i < SIN_LUT_SIZE; i++)
    {
        if ((i & 0x0F) == 0)
        {
            printf("\r\n    ");
        }
        int8_t sin_value = 127 * sin(2 * M_PI * i / SIN_LUT_SIZE);
        printf("%4d,", sin_value);
    }

    printf("\b \r\n}");
    
    while (true);
}