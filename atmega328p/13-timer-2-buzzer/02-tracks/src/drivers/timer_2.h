#ifndef TIMER_2_H_
#define TIMER_2_H_

#include "gpio.h"

// Small octave
#define C3          (0)
#define C3_SHARP    (1)
#define D3_FLAT     (1)
#define D3          (2)
#define D3_SHARP    (3)
#define E3_FLAT     (3)
#define E3          (4)
#define F3          (5)
#define F3_SHARP    (6)
#define G3_FLAT     (6)
#define G3          (7)
#define G3_SHARP    (8)
#define A3_FLAT     (8)
#define A3          (9)
#define A3_SHARP    (10)
#define B3_FLAT     (10)
#define B3          (11)

// 1-line octave
#define C4          (12)
#define C4_SHARP    (13)
#define D4_FLAT     (13)
#define D4          (14)
#define D4_SHARP    (15)
#define E4_FLAT     (15)
#define E4          (16)
#define F4          (17)
#define F4_SHARP    (18)
#define G4_FLAT     (18)
#define G4          (19)
#define G4_SHARP    (20)
#define A4_FLAT     (20)
#define A4          (21)
#define A4_SHARP    (22)
#define B4_FLAT     (22)
#define B4          (23)

// 2-line octave
#define C5          (24)

void play_tone(uint8_t note, uint16_t interval_duration, uint8_t note_part);
void mute(uint16_t mute_duration);

#endif /* TIMER_2_H_ */