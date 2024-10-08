/*
 * gpio.h
 *
 * Created: 02/04/2023 12:01:32
 * Author : Maksym_Palii
 */ 

#ifndef GPIO_H_
#define GPIO_H_

#include <avr/io.h>

/*
 * General purpose IO pins handling
 */

typedef enum 
{
	PB_0, PB_1, PB_2, PB_3, PB_4, PB_5, PB_6, PB_7,
	PD_0, PD_1, PD_2, PD_3, PD_4, PD_5, PD_6, PD_7,
	PC_0, PC_1, PC_2, PC_3, PC_4, PC_5, PC_6
} gpio_generic_e;

typedef enum
{
	GPIO_UNUSED_01				= PB_0,
	HC_SR04_TRIGGER_BR			= PB_1,
	HC_SR04_ECHO_BR				= PB_2,
	GPIO_UNUSED_04				= PB_3,
	GPIO_UNUSED_05				= PB_4,
	GPIO_UNUSED_06				= PB_5,
	GPIO_UNUSED_07				= PB_6,
	GPIO_UNUSED_08				= PB_7,
	
	RX							= PD_0,
	TX							= PD_1,
	GPIO_UNUSED_11				= PD_2,
	HC_SR04_TRIGGER_TL			= PD_3,
	HC_SR04_ECHO_TL				= PD_4,
	GPIO_UNUSED_14				= PD_5,
	HC_SR04_TRIGGER_BL			= PD_6,
	HC_SR04_ECHO_BL				= PD_7,
	
	HC_SR04_TRIGGER_TR			= PC_0,
	HC_SR04_ECHO_TR				= PC_1,
	GPIO_UNUSED_19				= PC_2,
	GPIO_UNUSED_20				= PC_3,
	GPIO_UNUSED_21				= PC_4,
	GPIO_UNUSED_22				= PC_5,
	GPIO_UNUSED_23				= PC_6
} gpio_e;

typedef enum
{
	INPUT,
	OUTPUT
} gpio_direction_e;

typedef enum
{
	LOW,		// or high impedance state
	HIGH		// or pull-up
} gpio_data_e;

void gpio_set_direction(gpio_e gpio, gpio_direction_e direction);
void gpio_set_data(gpio_e gpio, gpio_data_e data);
gpio_data_e gpio_get_input(gpio_data_e gpio);
void gpio_init(void);
void loop_while_gpio_is_low(gpio_e gpio);

#endif /* GPIO_H_ */