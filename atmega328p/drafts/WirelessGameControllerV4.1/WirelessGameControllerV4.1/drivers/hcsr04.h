/*
 * hcsr04.h
 *
 * Created: 02/04/2023 16:26:20
 *  Author: Maksym_Palii
 */ 


#ifndef HCSR04_H_
#define HCSR04_H_

#define F_CPU 18432000UL

#include "gpio.h"
#include "uart.h"
#include <util/delay.h>
#include <stdbool.h>

void generate_ultrasonic_impulse(gpio_e trigger, gpio_e echo);
void handle_sensor(gpio_e echo, bool *sensor_was_triggered, char *high_code, char *low_code);

#endif /* HCSR04_H_ */