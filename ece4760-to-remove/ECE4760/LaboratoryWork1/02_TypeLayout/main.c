/*
 * avr-gcc type layout, https://gcc.gnu.org/wiki/avr-gcc#Type_Layout
 *
 * Created: 21/01/2023 23:12:45
 * Author : Maksym Palii
 */ 

#include <avr/io.h>
#include <stddef.h>
#include <stdbool.h>

void init_io_pins(void)
{
    // Configure data direction for pins 0-7 (port D) as OUTPUT
    DDRD = 0xFF;
}

int main(void)
{
    init_io_pins();
	
    // Implementation-specific data type, for avr-gcc is a 'long unsigned int'
    size_t result;

    // 1 byte
    result = sizeof(char);
    //result = sizeof(unsigned char);
    //result = sizeof(signed char);

    // 2 bytes
    //result = sizeof(int);
    //result = sizeof(unsigned int);
    //result = sizeof(signed int);

    // 4 bytes
    //result = sizeof(long int);
    //result = sizeof(long unsigned int);
    //result = sizeof(long signed int);

    // 8 bytes
    //result = sizeof(long long int);
    //result = sizeof(long long unsigned int);
    //result = sizeof(long long signed int);

    // 2 bytes
    //result = sizeof(short int);
    //result = sizeof(short unsigned int);
    //result = sizeof(short signed int);

    // 4 bytes
    //result = sizeof(float);
    //result = sizeof(double);
    //result = sizeof(long double);

    // 1 byte
    //result = sizeof(void);

    // 2 bytes
    //result = sizeof(char *);
    //result = sizeof(int *);
    //result = sizeof(long *);
    //result = sizeof(long long *);
    //result = sizeof(float *);
    //result = sizeof(double *);
    //result = sizeof(void *);

    // 1 byte
    //result = sizeof(uint8_t);
    //result = sizeof(int8_t);

    // 2 bytes
    //result = sizeof(uint16_t);
    //result = sizeof(int16_t);

    // 4 bytes
    //result = sizeof(uint32_t);
    //result = sizeof(int32_t);

    // 8 bytes
    //result = sizeof(uint64_t);
    //result = sizeof(int64_t);

    //result = sizeof(0xFF);                // 2 bytes
    //result = sizeof(0xffFF);              // 2 bytes
    //result = sizeof(0xFFffFF);            // 4 bytes
    //result = sizeof(0xFFffFFffFFffFF);    // 4 bytes

    // Show result in port D
    PORTD = result;
	
    while (true) 
    {
        // No logic
    }
}
