/**
 * @author Maksym Palii
 * @brief Nirvana - Come As You Are (intro sequencer)
 * @version 1.0
 * @date 2024 September 28
 */

#define F_CPU           (18432000UL)
#define MAX_AMPLITUDE   (0xFFFF)
#define PHASE_FACTOR    (4)     // 65536 / 16384 = 4;

#include "drivers/gpio.h"   
#include "drivers/timer0.h"
#include "drivers/timer1.h"
#include "util/lut.h"
#include <avr/interrupt.h>

// Octave 2
// #define D  (73)
// #define Eb (78)
// #define E  (82)
// #define G  (98)
// #define A  (110)

// Octave 3
// #define D  (147)
// #define Eb (156)
// #define E  (165)
// #define G  (196)
// #define A  (220)

// Octave 4
#define D  (294)
#define Eb (311)
#define E  (330)
#define G  (392)
#define A  (440)


int16_t tone[] =    {   D,      D,      Eb,     E,      G,      E,      G,      E,      E,      Eb,     D,      A,      D,      D,      A   };
int8_t duration[] = {   1,      1,      1,      2,      1,      1,      1,      1,      1,      1,      1,      1,      1,      2,      1   };
int8_t note_index = 0;

// DDS specific section
volatile int16_t frequency1 = 0;         // TONE
const int8_t tau_rise_1 = 2;
const int8_t tau_fall_1 = 6;
volatile uint16_t phase_counter_1 = 0;
volatile uint16_t amplitude_rise_1 = MAX_AMPLITUDE;
volatile uint16_t amplitude_fall_1 = MAX_AMPLITUDE;

// DDS preacaler
volatile uint8_t prescaler = 0;
// Pace prescaler
volatile uint8_t pace_prescaler = 0;
// Note duration
volatile int8_t note_duration_counter = 0;

ISR (TIMER1_COMPA_vect, ISR_NAKED)
{
    // phases
    phase_counter_1 += frequency1 * PHASE_FACTOR;

    // the (prescaler & 0xFF) slows down the decay computation by 256 times
    if ((prescaler & 0xFF) == 0)
    {
        amplitude_rise_1 = amplitude_rise_1 - (amplitude_rise_1 >> tau_rise_1);
        amplitude_fall_1 = amplitude_fall_1 - (amplitude_fall_1 >> tau_fall_1);

        pace_prescaler++;
        if (pace_prescaler == 17) 
        {
            pace_prescaler = 0;

            if (note_duration_counter == 0)
            {
                note_duration_counter = duration[note_index] - 1;
                frequency1 = tone[note_index];

                // amplitude_rise_1 = MAX_AMPLITUDE;
                // amplitude_fall_1 = MAX_AMPLITUDE;

                // amplitude syncronization
                uint16_t amplitude_rise_old = amplitude_rise_old;
                amplitude_rise_1 = MAX_AMPLITUDE - amplitude_fall_1;
                amplitude_fall_1 = MAX_AMPLITUDE - amplitude_rise_old;
                
                note_index++;
                if (note_index > 14)
                {
                    note_index = 1;
                }
            } 
            else
            {
                note_duration_counter--;
            }
        }
    }

    // amplitudes
    uint8_t rise_1 = (MAX_AMPLITUDE - amplitude_rise_1) >> 8;
    uint8_t fall_1 = amplitude_fall_1 >> 8;
    uint8_t gain_1 = ((uint16_t) rise_1 * fall_1) >> 8;
    uint8_t phase_1 = phase_counter_1 >> 8;
    uint8_t amplitude_1 = ((uint16_t) gain_1 * lookup_sin[phase_1]) >> 8;

    // uint8_t rise_2 = (MAX_AMPLITUDE - amplitude_rise_2) >> 8;
    // uint8_t fall_2 = amplitude_fall_2 >> 8;
    // uint8_t gain_2 = ((uint16_t) rise_2 * fall_2) >> 8;
    // uint8_t phase_2 = phase_counter_2 >> 8;
    // uint8_t amplitude_2 = ((uint16_t) gain_2 * lookup_sin[phase_2]) >> 8;

    // uint8_t rise_3 = (MAX_AMPLITUDE - amplitude_rise_3) >> 8;
    // uint8_t fall_3 = amplitude_fall_3 >> 8;
    // uint8_t gain_3 = ((uint16_t) rise_3 * fall_3) >> 8;
    // uint8_t phase_3 = phase_counter_3 >> 8;
    // uint8_t amplitude_3 = ((uint16_t) gain_3 * lookup_sin[phase_3]) >> 8;

    // uint8_t rise_4 = (MAX_AMPLITUDE - amplitude_rise_4) >> 8;
    // uint8_t fall_4 = amplitude_fall_4 >> 8;
    // uint8_t gain_4 = ((uint16_t) rise_4 * fall_4) >> 8;
    // uint8_t phase_4 = phase_counter_4 >> 8;
    // uint8_t amplitude_4 = ((uint16_t) gain_4 * lookup_sin[phase_4]) >> 8;

    // set output
    uint8_t duty = (uint8_t) (amplitude_1 + 127);
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
    sei();

    while (true);
}   
  