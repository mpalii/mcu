/*
 * @author Maksym Palii
 * @brief DS18B20
 * @version 1.0
 * @date 2024 August 05
 */

#define F_CPU (8000000UL)

#include <stdbool.h>
#include <util/delay.h>
#include "drivers/gpio.h"

bool line_is_ready(void);

int main(void)
{
	init_gpio();
	
	while (true)
	{
		if (line_is_ready())
			GPIO_HIGH(SIGNAL_LED);
		else
    		GPIO_LOW(SIGNAL_LED);
	}
}

bool line_is_ready(void)
{
	GPIO_SET_OUTPUT(LINE_1_WIRE);
	_delay_us(500);

	GPIO_SET_INPUT(LINE_1_WIRE);
	_delay_us(60 + 60);

	bool is_ready = GPIO_GET_INPUT(LINE_1_WIRE) ? false : true;
	_delay_us(380);

	return is_ready;
}
