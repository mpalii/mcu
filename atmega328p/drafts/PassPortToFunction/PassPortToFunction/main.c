/*
 * PassPortToFunction.c
 *
 * Created: 01/04/2023 21:00:41
 * Author : Maksym_Palii
 */ 

#include <avr/io.h>

int main(void)
{
	//*(unsigned char *)(0x2a) = 0b00000001;	// Configure data direction for pin 0 (port D) as OUTPUT
	//*(unsigned char *)(0x2b) = 0b00000001;	// Set pin 0 (port D) driven high
	
	
	*(unsigned char *)(&DDRD) |= 0b00000001;	// Configure data direction for pin 0 (port D) as OUTPUT
	*(unsigned char *)(&PORTD) |= 0b00000001;	// Set pin 0 (port D) driven high
	
    while (1) 
    {
		// No logic
    }
}

