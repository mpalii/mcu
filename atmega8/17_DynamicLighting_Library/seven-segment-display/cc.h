/*
 * Created: 06.11.2021 11:51:13
 *  Author: Maksym Palii
 */ 

#ifndef PINS_H_
#define PINS_H_


void print7SEG(uint16_t value);
void init7SEG(void);

// 7SEG number of digits
#define TOTAL_DIGITS (4)

// 7SEG number of digits
#define TOTAL_SEGMENTS (8)

// Pin 11, corresponds to segment A
#define DDR_SEG_A (DDRD)
#define PORT_SEG_A (PORTD)
#define PIN_SEG_A (0)

// Pin 7, corresponds to segment B
#define DDR_SEG_B (DDRD)
#define PORT_SEG_B (PORTD)
#define PIN_SEG_B (1)

// Pin 4, corresponds to segment C
#define DDR_SEG_C (DDRD)
#define PORT_SEG_C (PORTD)
#define PIN_SEG_C (2)

// Pin 2, corresponds to segment D
#define DDR_SEG_D (DDRD)
#define PORT_SEG_D (PORTD)
#define PIN_SEG_D (3)

// Pin 1, corresponds to segment E
#define DDR_SEG_E (DDRD)
#define PORT_SEG_E (PORTD)
#define PIN_SEG_E (4)

// Pin 10, corresponds to segment F
#define DDR_SEG_F (DDRD)
#define PORT_SEG_F (PORTD)
#define PIN_SEG_F (5)

// Pin 5, corresponds to segment G
#define DDR_SEG_G (DDRD)
#define PORT_SEG_G (PORTD)
#define PIN_SEG_G (6)

// Pin , corresponds to segment DP
#define DDR_SEG_DP (DDRD)
#define PORT_SEG_DP (PORTD)
#define PIN_SEG_DP (7)

// Pin 6, corresponds to DIGIT 4 (on the right)
#define DDR_CC1 (DDRC)
#define PORT_CC1 (PORTC)
#define PIN_CC1 (0)

// Pin 8, corresponds to DIGIT 3
#define DDR_CC2 (DDRC)
#define PORT_CC2 (PORTC)
#define PIN_CC2 (1)

// Pin 9, corresponds to DIGIT 2
#define DDR_CC3 (DDRC)
#define PORT_CC3 (PORTC)
#define PIN_CC3 (2)

// Pin 14, corresponds to DIGIT 1 (on the left)
#define DDR_CC4 (DDRC)
#define PORT_CC4 (PORTC)
#define PIN_CC4 (3)


#endif /* PINS_H_ */