/**
 * @author Maksym Palii
 * @brief FM modulation
 * @version 2.0
 * @date 2024 September 23
 */

#define F_CPU           (18432000UL)
#define MAX_AMPLITUDE   (0xFFFF)
#define PHASE_FACTOR    (4)     // 65536 / 16384 = 4;

// rise and fall SHIFT factor  -- bigger is slower
// 6 implies tau of 64 cycles
// 8 implies tau of 256 cycles
// max value is 8

// FM modulation depth SHIFT factor 
// bigger factor implies smaller FM!
// useful range is 4 to 15

// Default:
#define MAIN_FREQUENCY  (261)
#define MAIN_TAU_RISE   (0)
#define MAIN_TAU_FALL   (4)
#define FM_FREQUENCY    (65)
#define FM_TAU_FALL     (6)
#define FM_DEPTH        (7)

// Chime:
// #define MAIN_FREQUENCY  (261)
// #define MAIN_TAU_RISE   (1)
// #define MAIN_TAU_FALL   (5)
// #define FM_FREQUENCY    (350)
// #define FM_TAU_FALL     (5)
// #define FM_DEPTH        (9)

// Plucked String 1:
// #define MAIN_FREQUENCY  (500)
// #define MAIN_TAU_RISE   (1)
// #define MAIN_TAU_FALL   (3)
// #define FM_FREQUENCY    (750)
// #define FM_TAU_FALL     (3)
// #define FM_DEPTH        (8)

// Plucked String 2:
// #define MAIN_FREQUENCY  (600)
// #define MAIN_TAU_RISE   (0)
// #define MAIN_TAU_FALL   (5)
// #define FM_FREQUENCY    (150)
// #define FM_TAU_FALL     (6)
// #define FM_DEPTH        (8)

// Bowed string:
// #define MAIN_FREQUENCY  (300)
// #define MAIN_TAU_RISE   (4)
// #define MAIN_TAU_FALL   (5)
// #define FM_FREQUENCY    (300)
// #define FM_TAU_FALL     (6)
// #define FM_DEPTH        (8)

// Small, stiff rod:
// #define MAIN_FREQUENCY  (1440)
// #define MAIN_TAU_RISE   (1)
// #define MAIN_TAU_FALL   (3)
// #define FM_FREQUENCY    (50) // at 100 get stiff string; at 200 get hollow pipe
// #define FM_TAU_FALL     (5)
// #define FM_DEPTH        (10) // or 9

// Bell/chime:
// #define MAIN_FREQUENCY  (1440)
// #define MAIN_TAU_RISE   (1)
// #define MAIN_TAU_FALL   (5)
// #define FM_FREQUENCY    (600)
// #define FM_TAU_FALL     (6)
// #define FM_DEPTH        (8)

// Bell:
// #define MAIN_FREQUENCY  (300)
// #define MAIN_TAU_RISE   (0)
// #define MAIN_TAU_FALL   (5)
// #define FM_FREQUENCY    (1000)
// #define FM_TAU_FALL     (6)
// #define FM_DEPTH        (8)

#include "drivers/gpio.h"   
#include "drivers/timer0.h"
#include "drivers/timer1.h"
#include <avr/interrupt.h>

const int8_t sine[] =
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
volatile uint16_t main_phase_counter = 0;
volatile uint16_t main_amplitude_rise = MAX_AMPLITUDE;
volatile uint16_t main_amplitude_fall = MAX_AMPLITUDE;
volatile uint16_t fm_phase_counter = 0;
volatile uint16_t fm_amplitude_fall = MAX_AMPLITUDE;
volatile uint8_t prescaler = 0;

ISR (TIMER1_COMPA_vect, ISR_NAKED)
{
    main_phase_counter += MAIN_FREQUENCY * PHASE_FACTOR;
    fm_phase_counter += FM_FREQUENCY * PHASE_FACTOR;

    // the (prescaler & 0xFF) slows down the decay computation by 256 times
    if ((prescaler & 0xFF) == 0)
    {
        main_amplitude_rise = main_amplitude_rise - (main_amplitude_rise >> MAIN_TAU_RISE);
        main_amplitude_fall = main_amplitude_fall - (main_amplitude_fall >> MAIN_TAU_FALL);
        fm_amplitude_fall = fm_amplitude_fall - (fm_amplitude_fall >> FM_TAU_FALL);
    }

    uint8_t main_rise = (MAX_AMPLITUDE - main_amplitude_rise) >> 8;
    uint8_t main_fall = main_amplitude_fall >> 8;
    uint8_t main_amplitude = ((uint16_t) main_rise * main_fall) >> 8;

    uint8_t main_phase = (uint8_t) (main_phase_counter >> 8);
    uint8_t fm_phase = (uint8_t) (fm_phase_counter >> 8);
    int8_t fm_amplitude = sine[fm_phase];

    uint8_t result_phase = main_phase + ((fm_amplitude * ((int16_t) (fm_amplitude_fall >> 8))) >> FM_DEPTH);

    uint8_t out = 128 + (((uint16_t) main_amplitude * sine[result_phase]) >> 8);
    set_duty(out);

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
