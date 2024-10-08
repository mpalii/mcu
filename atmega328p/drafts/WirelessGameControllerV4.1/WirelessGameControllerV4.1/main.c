/*
 * WirelessGameControllerV4.1.c
 *
 * Created: 02/04/2023 11:06:11
 * Author : Maksym_Palii
 */ 

#define F_CPU 18432000UL

#include <avr/interrupt.h>
#include <stdbool.h>
#include "drivers/gpio.h"
#include "drivers/timer0.h"
#include "drivers/hcsr04.h"
#include "drivers/uart.h"

enum EUltrasonicSensor{TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT};
enum EUltrasonicSensor current_sensor = TOP_LEFT;

bool sensor_1_was_triggered = false;
bool sensor_2_was_triggered = false;
bool sensor_3_was_triggered = false;
bool sensor_4_was_triggered = false;

//**********************************************************
// Task 1
#define t1 25		// 40(38) - regular delay; 30 - works fine
void task1(void);
volatile uint8_t time1;

//**********************************************************
//timer 0 compare ISR
ISR(TIMER0_COMPA_vect)
{      
  //Decrement buttons handler task timer if it is not already zero
  if (time1 > 0) --time1;
}

int main(void)
{	
	// delay for stabilization
	_delay_ms(1000);
	gpio_init();
	init_timer0();
	UART_init(F_CPU, 9600, false);
	sei();
	
    while (true)
    {
	    if (time1 == 0) task1();
    }
}

void task1(void)
{
	// re-initialize timer 1
	time1 = t1;
	
	if (current_sensor == BOTTOM_RIGHT)
	{
		generate_ultrasonic_impulse(HC_SR04_TRIGGER_BR, HC_SR04_ECHO_BR);
		handle_sensor(HC_SR04_ECHO_BR, &sensor_1_was_triggered, "<014;", "<018;");
		current_sensor = BOTTOM_LEFT;
		return;
	}
	
	if (current_sensor == BOTTOM_LEFT)
	{
		generate_ultrasonic_impulse(HC_SR04_TRIGGER_BL, HC_SR04_ECHO_BL);
		handle_sensor(HC_SR04_ECHO_BL, &sensor_2_was_triggered, "<012;", "<016;");
		current_sensor = TOP_LEFT;
		return;
	}
	
	if (current_sensor == TOP_LEFT)
	{
		generate_ultrasonic_impulse(HC_SR04_TRIGGER_TL, HC_SR04_ECHO_TL);
		handle_sensor(HC_SR04_ECHO_TL, &sensor_3_was_triggered, "<011;", "<015;");
		current_sensor = TOP_RIGHT;
		return;
	}
	
	if (current_sensor == TOP_RIGHT)
	{
		generate_ultrasonic_impulse(HC_SR04_TRIGGER_TR, HC_SR04_ECHO_TR);
		handle_sensor(HC_SR04_ECHO_TR, &sensor_4_was_triggered, "<013;", "<017;");
		current_sensor = BOTTOM_RIGHT;
		return;
	}
}

