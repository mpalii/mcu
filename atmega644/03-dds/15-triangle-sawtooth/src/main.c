/*
 * @author Maksym Palii
 * @brief Triangle and Sawtooth lookup tables (full period)
 * @version 1.0
 * @date 2024 September 28
 */

#define F_CPU               (18432000UL)
#define BAUD_RATE           (9600UL)
#define LUT_SIZE            (256)

#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "drivers/gpio.h"
#include "drivers/uart.h"

int main(void)
{
    init_gpio();
    init_uart(F_CPU, BAUD_RATE, false);

    printf("const int8_t tri_table[256] =\r\n{");
    for (uint16_t i = 0; i < LUT_SIZE; i++)
    {
        if ((i & 0x0F) == 0)
        {
            printf("\r\n    ");
        }
        int8_t tri_value = i < 64 ? i : (i < 192) ? 128-i : i-256;
        printf("%4d,", tri_value);
    }

    printf("\b \r\n}\r\n\r\n");

    printf("const int8_t saw_table[256] =\r\n{");
    for (uint16_t i = 0; i < LUT_SIZE; i++)
    {
        if ((i & 0x0F) == 0)
        {
            printf("\r\n    ");
        }
        int8_t saw_value = (char)(( (i<17)? i*7 : (i<241)? 128-i : i*7-1792 ));
        printf("%4d,", saw_value);
    }

    printf("\b \r\n}");
    
    while (true);
}