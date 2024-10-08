/**
 * @file main.c
 * @author Maksym Palii
 * @brief Example 05 - EMI (electromagnetic interference)  
 * @version 0.1
 * @date 2022-04-21
 */

#include <avr/io.h>

int main(void)
{
    *(unsigned char *)(0x2A) = 0b00000001;	// Configure data direction for pin 0 (port D) as OUTPUT

    unsigned char volatile * pinb_register = (unsigned char volatile *) 0x23;       // work fine
    //unsigned char * pinb_register = (unsigned char *) 0x23;                         // not work

    while (1)
    {
        if (*pinb_register & (1 << 0)) {
            //PORTD ^= 1;
            //_SFR_IO8(0x0B) ^= 1;
            //_MMIO_BYTE(0x2B) ^= 1;
            //(*(volatile unsigned char *)(0x2B)) ^= 1;
            (*(volatile unsigned char *)(0x2B)) ^= 1;



            //*(unsigned char *)(0x2b) ^= 1;
        }
    }
}
