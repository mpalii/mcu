/**
 * @author Maksym Palii
 * @brief Sine wave generation
 * @version 2.0
 * @date 2024 September 21
 */

#define F_CPU           (18432000UL)
#define MAX_AMPLITUDE   (0xFFFF)
#define FRACTIONAL_PART (6)  // 16384 / 256 = 64; 64 = 2 pow 6

#define FREQUENCY_HZ    (261)
#define TAU_RISE        (1)
#define TAU_FALL        (4)

#include "drivers/gpio.h"   
#include "drivers/timer0.h"
#include "drivers/timer1.h"
#include <avr/interrupt.h>

const int8_t sin_table[256] =
{
       0,   3,   6,   9,  12,  15,  18,  21,  24,  27,  30,  33,  36,  39,  42,  45,
      48,  51,  54,  57,  59,  62,  65,  67,  70,  73,  75,  78,  80,  82,  85,  87,
      89,  91,  94,  96,  98, 100, 102, 103, 105, 107, 108, 110, 112, 113, 114, 116,
     117, 118, 119, 120, 121, 122, 123, 123, 124, 125, 125, 126, 126, 126, 126, 126,
     127, 126, 126, 126, 126, 126, 125, 125, 124, 123, 123, 122, 121, 120, 119, 118,
     117, 116, 114, 113, 112, 110, 108, 107, 105, 103, 102, 100,  98,  96,  94,  91,
      89,  87,  85,  82,  80,  78,  75,  73,  70,  67,  65,  62,  59,  57,  54,  51,
      48,  45,  42,  39,  36,  33,  30,  27,  24,  21,  18,  15,  12,   9,   6,   3,
       0,  -3,  -6,  -9, -12, -15, -18, -21, -24, -27, -30, -33, -36, -39, -42, -45,
     -48, -51, -54, -57, -59, -62, -65, -67, -70, -73, -75, -78, -80, -82, -85, -87,
     -89, -91, -94, -96, -98,-100,-102,-103,-105,-107,-108,-110,-112,-113,-114,-116,
    -117,-118,-119,-120,-121,-122,-123,-123,-124,-125,-125,-126,-126,-126,-126,-126,
    -127,-126,-126,-126,-126,-126,-125,-125,-124,-123,-123,-122,-121,-120,-119,-118,
    -117,-116,-114,-113,-112,-110,-108,-107,-105,-103,-102,-100, -98, -96, -94, -91,
     -89, -87, -85, -82, -80, -78, -75, -73, -70, -67, -65, -62, -59, -57, -54, -51,
     -48, -45, -42, -39, -36, -33, -30, -27, -24, -21, -18, -15, -12,  -9,  -6,  -3 
};

// DDS specific section
volatile uint16_t phase_counter = 0;    // Fixed point: 2bits overflow + 8bits main + 6bits underflow (fractional part)
volatile uint16_t amplitude_rise = MAX_AMPLITUDE;
volatile uint16_t amplitude_fall = MAX_AMPLITUDE;
volatile uint8_t dynamic_counter = 0;

ISR (TIMER1_COMPA_vect, ISR_NAKED)
{
    phase_counter += FREQUENCY_HZ;

    if ((dynamic_counter & 0xFF) == 0)
    {
        amplitude_rise = amplitude_rise - (amplitude_rise >> TAU_RISE);
        amplitude_fall = amplitude_fall - (amplitude_fall >> TAU_FALL);
    }

    uint8_t rise = (MAX_AMPLITUDE - amplitude_rise) >> 8;
    uint8_t fall = amplitude_fall >> 8;
    uint8_t amplitude = ((uint16_t) rise * fall) >> 8;

    uint8_t phase = (uint8_t) (phase_counter >> FRACTIONAL_PART);
    uint8_t out = 127 + (((uint16_t) amplitude * sin_table[phase]) >> 8);
    set_duty(out);

    dynamic_counter++;

    asm("reti"::);
}

int main(void) 
{
    init_gpio();
    init_timer0();
    init_timer1();
    sei();

    while (true);
}
