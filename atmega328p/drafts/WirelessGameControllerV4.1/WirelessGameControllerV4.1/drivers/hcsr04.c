/*
 * hcsr04.c
 *
 * Created: 02/04/2023 16:26:34
 *  Author: Maksym_Palii
 */ 

#include "hcsr04.h"

void generate_ultrasonic_impulse(gpio_e trigger, gpio_e echo)
{
	// send 10 us pulse to trigger pin
	gpio_set_data(trigger, LOW);
	_delay_us(2);
	gpio_set_data(trigger, HIGH);
	_delay_us(10);
	gpio_set_data(trigger, LOW);
	
	loop_while_gpio_is_low(echo);
	_delay_us(2000);
}

void handle_sensor(gpio_e echo, bool *sensor_was_triggered, char *high_code, char *low_code)
{
	gpio_data_e input = gpio_get_input(echo);
	
	// check whether sensor was triggered
	if ((~input) && !*sensor_was_triggered)
	{
		*sensor_was_triggered = true;
		UART_transmit(high_code);
	}

	// check whether button was released
	if (INPUT && *sensor_was_triggered)
	{
		*sensor_was_triggered = false;
		UART_transmit(low_code);
	}
}
