/*
 * @author Maksym Palii
 * @brief Timer 2 - Imperial March
 * @version 1.0
 * @date 2024 April 26
 */

#define BPM (100UL)
#define INTERVAL (60000/BPM)

#include <stdbool.h>
#include "drivers/gpio.h"
#include "drivers/timer_2.h"

static inline void imperial_march(void);
static inline void c_major_scale_small_octave(void);
static inline void c_major_scale_1line_octave(void);

int main(void)
{
    gpio_init();

    //c_major_scale_small_octave();
    //c_major_scale_1line_octave();
    imperial_march();

    // buzz_off();

    while (true) 
    { 
        // NOP
    }
}

static inline void imperial_march(void)
{
    // 1st bar
    play_tone(G3, INTERVAL, 2);
    play_tone(G3, INTERVAL, 2);
    play_tone(G3, INTERVAL, 2);
    play_tone(E3_FLAT, INTERVAL*2/3, 2);
    play_tone(B3_FLAT, INTERVAL*1/3, 2);

    // 2nd bar
    play_tone(G3, INTERVAL, 2);
    play_tone(E3_FLAT, INTERVAL*2/3, 2);
    play_tone(B3_FLAT, INTERVAL*1/3, 2);
    play_tone(G3, INTERVAL*2, 4);

    // 3rd bar
    play_tone(D4, INTERVAL, 2);
    play_tone(D4, INTERVAL, 2);
    play_tone(D4, INTERVAL, 2);
    play_tone(E4_FLAT, INTERVAL*2/3, 2);
    play_tone(B3_FLAT, INTERVAL*1/3, 2);

    // 4th bar  
    play_tone(G3_FLAT, INTERVAL, 2);
    play_tone(E3_FLAT, INTERVAL*2/3, 2);
    play_tone(B3_FLAT, INTERVAL*1/3, 2);
    play_tone(G3, INTERVAL*2, 4);  

    // // 5th bar
    // play_tone(G4, INTERVAL, 2);
    // play_tone(G3, INTERVAL*2/3, 2);
    // play_tone(G3, INTERVAL*1/3, 2);
    // play_tone(G4, INTERVAL, 2);
    // play_tone(G4_FLAT, INTERVAL*2/3, 2);
    // play_tone(F3, INTERVAL*1/3, 2);

    // // 6th bar
    // play_tone(E4, INTERVAL*1/3, 2);
    // play_tone(D4_SHARP, INTERVAL*1/3, 2);
    // play_tone(E4, INTERVAL*1/3, 2);
    // mute(INTERVAL/2);
    // play_tone(G3_SHARP, INTERVAL/2, 2);
    // play_tone(C4_SHARP, INTERVAL, 2);
    // play_tone(B4, INTERVAL*2/3, 2);
    // play_tone(B4_FLAT, INTERVAL*1/3, 2);

}

static inline void c_major_scale_small_octave(void)
{
    play_tone(C3, INTERVAL, 2);
    play_tone(D3, INTERVAL, 2);
    play_tone(E3, INTERVAL, 2);
    play_tone(F3, INTERVAL, 2);
    play_tone(G3, INTERVAL, 2);
    play_tone(A3, INTERVAL, 2);
    play_tone(B3, INTERVAL, 2);
    play_tone(C4, INTERVAL, 2);
}

static inline void c_major_scale_1line_octave(void)
{
    play_tone(C4, INTERVAL, 2);
    play_tone(D4, INTERVAL, 2);
    play_tone(E4, INTERVAL, 2);
    play_tone(F4, INTERVAL, 2);
    play_tone(G4, INTERVAL, 2);
    play_tone(A4, INTERVAL, 2);
    play_tone(B4, INTERVAL, 2);
    play_tone(C5, INTERVAL, 2);
}
