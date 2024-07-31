/*
 * @author Maksym Palii
 * @brief Step motor 28BYJ-48 with ULN2003 driver
 * @version 1.0
 * @date 2024 July 27
 */

#define F_CPU (8000000UL)
#define STEP_DELAY (20)

#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>
#include "drivers/gpio.h"

static inline void in_low(void)
{
	GPIO_LOW(IN1);
	GPIO_LOW(IN2);
	GPIO_LOW(IN3);
	GPIO_LOW(IN4);
}

int main(void)
{
	init_gpio();

	_delay_ms(500);
	GPIO_HIGH(LED);
	_delay_ms(500);

	// Clockwise full-step mode
	for (uint16_t i = 0; i < 512; i++)
	{
		in_low();
		GPIO_HIGH(IN1);
		_delay_ms(STEP_DELAY);

		in_low();
		GPIO_HIGH(IN2);
		_delay_ms(STEP_DELAY);

		in_low();
		GPIO_HIGH(IN3);
		_delay_ms(STEP_DELAY);

		in_low();
		GPIO_HIGH(IN4);
		_delay_ms(STEP_DELAY);
	}


	// Anti-clockwise full-step mode
	for (uint16_t i = 0; i < 512; i++)
	{
		in_low();
		GPIO_HIGH(IN4);
		_delay_ms(STEP_DELAY);

		in_low();
		GPIO_HIGH(IN3);
		_delay_ms(STEP_DELAY);

		in_low();
		GPIO_HIGH(IN2);
		_delay_ms(STEP_DELAY);

		in_low();
		GPIO_HIGH(IN1);
		_delay_ms(STEP_DELAY);
	}

	// Clockwise half-step mode
	for (uint16_t i = 0; i < 512; i++)
	{
		in_low();
		GPIO_HIGH(IN1);
		_delay_ms(STEP_DELAY);

		in_low();
		GPIO_HIGH(IN1);
		GPIO_HIGH(IN2);
		_delay_ms(STEP_DELAY);

		in_low();
		GPIO_HIGH(IN2);
		_delay_ms(STEP_DELAY);

		in_low();
		GPIO_HIGH(IN2);
		GPIO_HIGH(IN3);
		_delay_ms(STEP_DELAY);

		in_low();
		GPIO_HIGH(IN3);
		_delay_ms(STEP_DELAY);

		in_low();
		GPIO_HIGH(IN3);
		GPIO_HIGH(IN4);
		_delay_ms(STEP_DELAY);

		in_low();
		GPIO_HIGH(IN4);
		_delay_ms(STEP_DELAY);

		in_low();
		GPIO_HIGH(IN4);
		GPIO_HIGH(IN1);
		_delay_ms(STEP_DELAY);
	}

	in_low();
	
	while (true)
	{
		// NOP
	}
}