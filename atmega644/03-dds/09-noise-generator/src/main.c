/**
 * @author Maksym Palii
 * @brief Sine wave generation
 * @version 2.0
 * @date 2024 September 15
 */

#define F_CPU (18432000UL)
#define BAUD_RATE (9600UL)

#define BIT_30  (0x40000000)    // 01000000 00000000 00000000 00000000
#define BIT_27  (0x08000000)    // 00001000 00000000 00000000 00000000

#include "drivers/gpio.h"   
#include "drivers/uart.h"
#include "drivers/timer0.h"
#include "drivers/timer1.h"
#include <avr/interrupt.h>

volatile bool bit_0;
volatile bool bit_1;
volatile uint8_t random;;
volatile uint32_t noise_generator;

ISR (TIMER1_COMPA_vect)
{
    set_duty(random);
}

int main(void) 
{
    init_gpio();
    init_uart();
    init_timer0();
    init_timer1();
    sei();

    noise_generator = 0xab5a55aa;   // some seed

    uart_transmit("Start up...\r\n");

    while (true)
    {
        bit_0 = noise_generator & BIT_27;
        bit_1 = noise_generator & BIT_30;
        noise_generator <<= 1;
        noise_generator += (bit_0 ^ bit_1);
        // random = (uint8_t) (noise_generator & 0x7f);     // normalized to 128 scale
        random = (uint8_t) noise_generator;
    }
}   
  