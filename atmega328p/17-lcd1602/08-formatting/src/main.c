/*
 * @author Maksym Palii
 * @brief LCD 1608 - 8bit mode
 * @version 1.0
 * @date 2024 July 06 
 */

#define F_CPU (8000000UL)

#include <avr/io.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include "drivers/gpio.h"
#include "drivers/lcd1602.h"

void print(char* array);

int main(void)
{
	init_gpio();
	init_lcd1602();

	/*Example 1 - itoa (stdlib.h)*/
	// char buffer[16];

	// // int num_1 = 65;
	// // print("num_1=");
	// // itoa(num_1, buffer, 10);

	// // int num_2 = -49;
	// // print("num_2=");
	// // itoa(num_2, buffer, 10);

	// // int num_3 = 347;
	// // print("num_3=");
	// // itoa(num_3, buffer, 10);

	// // int num_4 = 255;
	// // print("num_4=0b");
	// // itoa(num_4, buffer, 2);

	// // int num_5 = 255;
	// // print("num_5=0x");
	// // itoa(num_5, buffer, 16);
 
	// print(buffer);
 
	/*Example 2 - different values*/
	// char buffer[16];
    // char counter = 0;

	// while (true)
	// {
	// 	itoa(counter, buffer, 10);
	// 	send_command(0x01);	// clear display and set DDRAM address to 0
	// 	print(buffer);
	// 	counter++;
	// 	_delay_ms(500);
	// }

	/*Example 3 - float*/
	// char buffer[16];

	// // float num_6 = 25.8;
	// // print("num_6=");
	// // itoa(num_6, buffer, 10);

	// // float num_7 = -5.807;
	// // print("num_7=");
	// // int minimal_length = 9;
	// // int digit_number_after_dp = 4;	// try with 2 (rounding to -5.81)
	// // dtostrf(num_7, minimal_length, digit_number_after_dp, buffer);
 
	// print(buffer);

	/*Example 4 - sprintf*/
	// char buffer[16];

	// // sprintf(buffer, "Hello, World!");
	// // sprintf(buffer, "v1=%3d, v2=%04d", 64, -67);
	// // sprintf(buffer, "c1='%c', c2='%c'", 64, 'f');
	// // sprintf(buffer, "f1=%9.4f", -5.807);
	// // sprintf(buffer, "f1=%.1f,f2=%.2f", 25.53, -4.918);
	
	// print(buffer);


	while (true)
	{
		// NOP
	}
	
}

void print(char* array)
{
    uint8_t i = 0;
	while (array[i] != '\0')
	{
		send_data(array[i]);
		i++;	
	}
}
