/*
 * gpio.c
 *
 * Created: 02/04/2023 12:13:08
 * Author : Maksym_Palii
 */ 

#include "gpio.h"

#define GPIO_PORT_OFFSET (3U)
#define GPIO_PORT_MASK (0x3U << GPIO_PORT_OFFSET)
#define GPIO_PIN_MASK (0x7U)

static inline uint8_t gpio_port(gpio_e gpio)
{
	return (gpio & GPIO_PORT_MASK) >> GPIO_PORT_OFFSET;
}

static inline uint8_t gpio_pin_bit(gpio_e gpio)
{
	return 1 << (gpio & GPIO_PIN_MASK);
}

static volatile uint8_t *const port_data_register[] = 
{ 
	&PORTB, 
	&PORTD, 
	&PORTC 
};

static volatile uint8_t *const port_direction_register[] = 
{ 
	&DDRB, 
	&DDRD, 
	&DDRC 
};

static volatile uint8_t *const port_input_register[] = 
{ 
	&PINB, 
	&PIND, 
	&PINC 
};
	
void gpio_set_direction(gpio_e gpio, gpio_direction_e direction)
{
	const uint8_t port = gpio_port(gpio);
	const uint8_t pin = gpio_pin_bit(gpio);
	
	switch (direction)
	{
		case OUTPUT:
			*port_direction_register[port] |= pin;
			break;
		case INPUT:
			*port_direction_register[port] &= ~pin;
			break;
	}
}

void gpio_set_data(gpio_e gpio, gpio_data_e data)
{
	const uint8_t port = gpio_port(gpio);
	const uint8_t pin = gpio_pin_bit(gpio);
	
	switch (data)
	{
		case HIGH:
			*port_data_register[port] |= pin;
			break;
		case LOW:
			*port_data_register[port] &= ~pin;
			break;
	}
}

gpio_data_e gpio_get_input(gpio_data_e gpio)
{
	const uint8_t port = gpio_port(gpio);
	const uint8_t pin = gpio_pin_bit(gpio);
	
	return *port_input_register[port] & pin ? HIGH : LOW;
}

void loop_while_gpio_is_low(gpio_e gpio)
{
	const uint8_t port = gpio_port(gpio);
	const uint8_t pin = gpio_pin_bit(gpio);
	
	loop_until_bit_is_set(port_input_register[port], pin);
}

void gpio_init(void)
{
	gpio_set_direction(HC_SR04_TRIGGER_BL, OUTPUT);
	gpio_set_direction(HC_SR04_TRIGGER_BR, OUTPUT);
	gpio_set_direction(HC_SR04_TRIGGER_TL, OUTPUT);
	gpio_set_direction(HC_SR04_TRIGGER_TR, OUTPUT);
	
	gpio_set_direction(HC_SR04_ECHO_BL, LOW);
	gpio_set_direction(HC_SR04_ECHO_BR, LOW);
	gpio_set_direction(HC_SR04_ECHO_TL, LOW);
	gpio_set_direction(HC_SR04_ECHO_TR, LOW);
}
