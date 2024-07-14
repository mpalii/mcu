/**
 * @author Maksym Palii
 * @brief ADC and SMA filter (simple moving average)
 * @version 1.0
 * @date 2024 July 07
 */

#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "drivers/gpio.h"
#include "drivers/adc.h"
#include "drivers/lcd1602.h"
#include "drivers/timer0.h"

char buffer[16];

int16_t convert_as_decicelsius(uint16_t voltage_level)
{
    return (voltage_level - 500);
}

ISR (TIMER0_COMPA_vect)
{    
    // convert ADC conversion result to temperature and pass to split function
    uint16_t voltage_level = adc_get_conversion_result();
    int16_t temperature_in_decicelsius = convert_as_decicelsius(voltage_level);

    // render value
    memset(buffer, '\0', sizeof(buffer));
    send_command(0xC0);
    sprintf(buffer, "%3d.%1d%cC", (temperature_in_decicelsius / 10), abs(temperature_in_decicelsius % 10), 0b11011111);
    print(buffer);
}

int main(void)
{
    init_gpio();
    init_lcd1602();
    init_timer0();
    init_adc();
    sei();
	
    while (true)
    {
        // nop
    }
}
