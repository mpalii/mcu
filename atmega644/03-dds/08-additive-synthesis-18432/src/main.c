/**
 * @author Maksym Palii
 * @brief Sine wave generation
 * @version 2.0
 * @date 2024 September 15
 */

#define F_CPU (18432000UL)
#define BAUD_RATE (9600UL)

#include "drivers/gpio.h"   
#include "drivers/uart.h"
#include "drivers/timer0.h"
#include "drivers/timer1.h"
#include <avr/interrupt.h>

#define SAMPLING_RATIO (6)  // 16384 / 256 = 64; 64 = 2 pow 6

#define FREQUENCY_1 (220)
#define FREQUENCY_2 (0)
#define FREQUENCY_3 (0)
#define FREQUENCY_4 (0)

volatile uint16_t phase_counter_1 = 0;
volatile uint16_t phase_counter_2 = 0;
volatile uint16_t phase_counter_3 = 0;
volatile uint16_t phase_counter_4 = 0;

const int8_t sine_table[] = 
{
       0,   3,   6,   9,  12,  16,  19,  22,  25,  28,  31,  34,  37,  40,  43,  46,
      49,  51,  54,  57,  60,  63,  65,  68,  71,  73,  76,  78,  81,  83,  85,  88,
      90,  92,  94,  96,  98, 100, 102, 104, 106, 107, 109, 111, 112, 113, 115, 116,
     117, 118, 120, 121, 122, 122, 123, 124, 125, 125, 126, 126, 126, 127, 127, 127,
     127, 127, 127, 127, 126, 126, 126, 125, 125, 124, 123, 122, 122, 121, 120, 118,
     117, 116, 115, 113, 112, 111, 109, 107, 106, 104, 102, 100,  98,  96,  94,  92,
      90,  88,  85,  83,  81,  78,  76,  73,  71,  68,  65,  63,  60,  57,  54,  51,
      49,  46,  43,  40,  37,  34,  31,  28,  25,  22,  19,  16,  12,   9,   6,   3,
       0,  -3,  -6,  -9, -12, -16, -19, -22, -25, -28, -31, -34, -37, -40, -43, -46,
     -49, -51, -54, -57, -60, -63, -65, -68, -71, -73, -76, -78, -81, -83, -85, -88,
     -90, -92, -94, -96, -98,-100,-102,-104,-106,-107,-109,-111,-112,-113,-115,-116,
    -117,-118,-120,-121,-122,-122,-123,-124,-125,-125,-126,-126,-126,-127,-127,-127,
    -127,-127,-127,-127,-126,-126,-126,-125,-125,-124,-123,-122,-122,-121,-120,-118,
    -117,-116,-115,-113,-112,-111,-109,-107,-106,-104,-102,-100, -98, -96, -94, -92,
     -90, -88, -85, -83, -81, -78, -76, -73, -71, -68, -65, -63, -60, -57, -54, -51,
     -49, -46, -43, -40, -37, -34, -31, -28, -25, -22, -19, -16, -12,  -9,  -6,  -3
};

uint8_t i = 0;

ISR (TIMER1_COMPA_vect)
{
    phase_counter_1 += FREQUENCY_1;
    uint8_t phase_1 = (phase_counter_1 >> 6) & 0xFF;
    int8_t amplitude_1 = sine_table[phase_1] >> 2;

    phase_counter_2 += FREQUENCY_2;
    uint8_t phase_2 = (phase_counter_2 >> 6) & 0xFF;
    int8_t amplitude_2 = sine_table[phase_2] >> 2;

    phase_counter_3 += FREQUENCY_3;
    uint8_t phase_3 = (phase_counter_3 >> 6) & 0xFF;
    int8_t amplitude_3 = sine_table[phase_3] >> 2;

    phase_counter_4 += FREQUENCY_4;
    uint8_t phase_4 = (phase_counter_4 >> 6) & 0xFF;
    int8_t amplitude_4 = sine_table[phase_4] >> 2;

    int16_t amplitude_accumulator = 0;
    amplitude_accumulator += amplitude_1;
    amplitude_accumulator += amplitude_2;
    amplitude_accumulator += amplitude_3;
    amplitude_accumulator += amplitude_4;

    // if (amplitude_accumulator > 127) amplitude_accumulator = 127;
    // if (amplitude_accumulator < -127) amplitude_accumulator = -127;

    uint8_t duty = (amplitude_accumulator + 127) & 0xFF;
    set_duty(duty);
}

int main(void) 
{
    init_gpio();
    init_uart();
    init_timer0();
    init_timer1();
    sei();

    uart_transmit("Start up...\r\n");

    while (true);
}   
  