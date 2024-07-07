/**
 * @author Maksym Palii
 * @brief ADC noise cancelling and TMP36 analog sensor
 * @version 1.0
 * @date 2024 July 06
 */

#define F_CPU (8000000UL)

#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdbool.h>
#include <stdio.h>
#include <util/delay.h>
#include "drivers/gpio.h"
#include "drivers/adc.h"
#include "drivers/lcd1602.h"

void print(char* array)
{
    uint8_t i = 0;
	while (array[i] != '\0')
	{
		send_data(array[i]);
		i++;	
	}
}

int16_t convert_as_decicelsius(uint16_t voltage_level)
{
    return (voltage_level - 500);
}

int main(void)
{
    init_gpio();
    init_adc();
    init_lcd1602();

    sleep_enable();
    sei();

    print("Temperature:");
    char buffer[16];
	
    while (true)
    {
        sleep_cpu();

        uint16_t conversion_result = adc_get_conversion_result();
        int16_t decicelsius = convert_as_decicelsius(conversion_result);
        send_command(0xC0);
        sprintf(buffer, "%3d.%1d%cC", (decicelsius / 10), (decicelsius % 10), 0b11011111);
        print(buffer);

        _delay_ms(1000);
    }
}
