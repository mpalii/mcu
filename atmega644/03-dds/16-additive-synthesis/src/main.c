/**
 * @author Maksym Palii
 * @brief Additive synthesis
 * @version 1.0
 * @date 2024 September 28
 */

#define F_CPU           (18432000UL)
#define MAX_AMPLITUDE   (0x7FFF)
#define PHASE_FACTOR    (4)     // 65536 / 16384 = 4;

#include "drivers/gpio.h"   
#include "drivers/timer0.h"
#include "drivers/timer1.h"
#include "util/lut.h"
#include <avr/interrupt.h>

// DDS specific section
#define FREQUENCY_1 (262)
#define TAU_RISE_1  (1)
#define TAU_FALL_1  (5)
volatile uint16_t phase_counter_1 = 0;
volatile uint16_t amplitude_rise_1 = MAX_AMPLITUDE;
volatile uint16_t amplitude_fall_1 = MAX_AMPLITUDE;

#define FREQUENCY_2 (414)
#define TAU_RISE_2  (1)
#define TAU_FALL_2  (5)
volatile uint16_t phase_counter_2 = 0;
volatile uint16_t amplitude_rise_2 = MAX_AMPLITUDE;
volatile uint16_t amplitude_fall_2 = MAX_AMPLITUDE;

#define FREQUENCY_3 (587)
#define TAU_RISE_3  (1)
#define TAU_FALL_3  (4)
volatile uint16_t phase_counter_3 = 0;
volatile uint16_t amplitude_rise_3 = MAX_AMPLITUDE;
volatile uint16_t amplitude_fall_3 = MAX_AMPLITUDE;

#define TAU_RISE_N  (1)
#define TAU_FALL_N  (1)
volatile uint16_t amplitude_rise_n = MAX_AMPLITUDE;
volatile uint16_t amplitude_fall_n = MAX_AMPLITUDE;

// RANDOM
#define BIT_30  (0x40000000)    // 01000000 00000000 00000000 00000000
#define BIT_27  (0x08000000)    // 00001000 00000000 00000000 00000000
volatile bool bit_0;
volatile bool bit_1;
volatile uint8_t random;
volatile uint32_t noise_generator;

// DDS preacaler
volatile uint8_t prescaler = 0;

ISR (TIMER1_COMPA_vect, ISR_NAKED)
{
    // noise generating
    bit_0 = noise_generator & BIT_27;
    bit_1 = noise_generator & BIT_30;
    noise_generator <<= 1;
    noise_generator += (bit_0 ^ bit_1);
    random = (uint8_t) (noise_generator & 0x7f);     // normalized to 128 scale
    // random = (uint8_t) noise_generator;

    // include only periodic voices
    phase_counter_1 += FREQUENCY_1 * PHASE_FACTOR;
    phase_counter_2 += FREQUENCY_2 * PHASE_FACTOR;
    phase_counter_3 += FREQUENCY_3 * PHASE_FACTOR;

    // the (prescaler & 0xFF) slows down the decay computation by 256 times
    if ((prescaler & 0xFF) == 0)
    {
        amplitude_rise_1 = amplitude_rise_1 - (amplitude_rise_1 >> TAU_RISE_1);
        amplitude_fall_1 = amplitude_fall_1 - (amplitude_fall_1 >> TAU_FALL_1);

        amplitude_rise_2 = amplitude_rise_2 - (amplitude_rise_2 >> TAU_RISE_2);
        amplitude_fall_2 = amplitude_fall_2 - (amplitude_fall_2 >> TAU_FALL_2);

        amplitude_rise_3 = amplitude_rise_3 - (amplitude_rise_3 >> TAU_RISE_3);
        amplitude_fall_3 = amplitude_fall_3 - (amplitude_fall_3 >> TAU_FALL_3);

        amplitude_rise_n = amplitude_rise_n - (amplitude_rise_n >> TAU_RISE_N);
        amplitude_fall_n = amplitude_fall_n - (amplitude_fall_n >> TAU_FALL_N);
    }

    // amplitudes
    uint8_t rise_1 = (MAX_AMPLITUDE - amplitude_rise_1) >> 8;
    uint8_t fall_1 = amplitude_fall_1 >> 8;
    uint8_t gain_1 = ((uint16_t) rise_1 * fall_1) >> 8;
    uint8_t phase_1 = phase_counter_1 >> 8;
    uint8_t amplitude_1 = ((uint16_t) gain_1 * lookup[SIN][phase_1]) >> 8;

    uint8_t rise_2 = (MAX_AMPLITUDE - amplitude_rise_2) >> 8;
    uint8_t fall_2 = amplitude_fall_2 >> 8;
    uint8_t gain_2 = ((uint16_t) rise_2 * fall_2) >> 8;
    uint8_t phase_2 = phase_counter_2 >> 8;
    uint8_t amplitude_2 = ((uint16_t) gain_2 * lookup[SIN][phase_2]) >> 8;

    uint8_t rise_3 = (MAX_AMPLITUDE - amplitude_rise_3) >> 8;
    uint8_t fall_3 = amplitude_fall_3 >> 8;
    uint8_t gain_3 = ((uint16_t) rise_3 * fall_3) >> 8;
    uint8_t phase_3 = phase_counter_3 >> 8;
    uint8_t amplitude_3 = ((uint16_t) gain_3 * lookup[SIN][phase_3]) >> 8;

    uint8_t rise_n = (MAX_AMPLITUDE - amplitude_rise_n) >> 8;
    uint8_t fall_n = amplitude_fall_n >> 8;
    uint8_t gain_n = ((uint16_t) rise_n * fall_n) >> 8;
    uint8_t amplitude_n = ((uint16_t) gain_n * random) >> 8;
    
    int16_t amplitude_accumulator = 0;
    amplitude_accumulator += amplitude_1;
    amplitude_accumulator += amplitude_2;
    amplitude_accumulator += amplitude_3;
    amplitude_accumulator += amplitude_n;

    // set output
    uint8_t duty = (uint8_t) (amplitude_accumulator + 127);
    set_duty(duty);

    // increase prescaler
    prescaler++;

    asm("reti"::);
}

int main(void) 
{
    init_gpio();
    init_timer0();
    init_timer1();
    noise_generator = 0xab5a55aa;   // some seed
    sei();

    while (true);
}   
  