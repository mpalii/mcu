/**
 * @author Maksym Palii
 * @brief Button (keyboard) matrix
 * @version 1.0
 * @date 2024 March 24
 */

#define F_CPU (8000000UL)

#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>

bool button_1_was_pressed = false;
bool button_2_was_pressed = false;
bool button_3_was_pressed = false;
bool button_4_was_pressed = false;
bool button_5_was_pressed = false;
bool button_6_was_pressed = false;
bool button_7_was_pressed = false;
bool button_8_was_pressed = false;
bool button_9_was_pressed = false;

static inline void init_pins(void)
{
    DDRB |= _BV(PB0);
    DDRC |= _BV(PC0) | _BV(PC1) | _BV(PC2);
    DDRD = 0xFF;
}

/*=======================================================================*/
static inline void check_column_147(void)
{
        /* Enable column 1 (buttons: B1, B4, B7) */
        PORTC |= _BV(PC0);
        
        /* Button B1 */
        // check whether button was pressed
        if (bit_is_set(PINC, PC3) && !button_1_was_pressed)
        {
            button_1_was_pressed = true;
            PORTD ^= _BV(PD0);
        }
        
        // check whether button was released
        if (bit_is_clear(PINC, PC3) && button_1_was_pressed)
        {
            button_1_was_pressed = false;
        }

        /* Button B4 */
        // check whether button was pressed
        if (bit_is_set(PINC, PC4) && !button_4_was_pressed)
        {
            button_4_was_pressed = true;
            PORTD ^= _BV(PD3);
        }
        
        // check whether button was released
        if (bit_is_clear(PINC, PC4) && button_4_was_pressed)
        {
            button_4_was_pressed = false;
        }

        /* Button B7 */
        // check whether button was pressed
        if (bit_is_set(PINC, PC5) && !button_7_was_pressed)
        {
            button_7_was_pressed = true;
            PORTD ^= _BV(PD6);
        }
        
        // check whether button was released
        if (bit_is_clear(PINC, PC5) && button_7_was_pressed)
        {
            button_7_was_pressed = false;
        }

        /* Disable column 1 (buttons: B1, B4, B7) */
        PORTC &= ~_BV(PC0);
}

/*=======================================================================*/
static inline void check_column_258(void)
{
        /* Enable column 2 (buttons: B2, B5, B8) */
        PORTC |= _BV(PC1);
        
        /* Button B2 */
        // check whether button was pressed
        if (bit_is_set(PINC, PC3) && !button_2_was_pressed)
        {
            button_2_was_pressed = true;
            PORTD ^= _BV(PD1);
        }
        
        // check whether button was released
        if (bit_is_clear(PINC, PC3) && button_2_was_pressed)
        {
            button_2_was_pressed = false;
        }

        /* Button B5 */
        // check whether button was pressed
        if (bit_is_set(PINC, PC4) && !button_5_was_pressed)
        {
            button_5_was_pressed = true;
            PORTD ^= _BV(PD4);
        }
        
        // check whether button was released
        if (bit_is_clear(PINC, PC4) && button_5_was_pressed)
        {
            button_5_was_pressed = false;
        }

        /* Button B8 */
        // check whether button was pressed
        if (bit_is_set(PINC, PC5) && !button_8_was_pressed)
        {
            button_8_was_pressed = true;
            PORTD ^= _BV(PD7);
        }
        
        // check whether button was released
        if (bit_is_clear(PINC, PC5) && button_8_was_pressed)
        {
            button_8_was_pressed = false;
        }

        /* Disable column 1 (buttons: B2, B5, B8) */
        PORTC &= ~_BV(PC1);
}

/*=======================================================================*/
static inline void check_column_369(void)
{
        /* Enable column 3 (buttons: B3, B6, B6) */
        PORTC |= _BV(PC2);
        
        /* Button B3 */
        // check whether button was pressed
        if (bit_is_set(PINC, PC3) && !button_3_was_pressed)
        {
            button_3_was_pressed = true;
            PORTD ^= _BV(PD2);
        }
        
        // check whether button was released
        if (bit_is_clear(PINC, PC3) && button_3_was_pressed)
        {
            button_3_was_pressed = false;
        }

        /* Button B6 */
        // check whether button was pressed
        if (bit_is_set(PINC, PC4) && !button_6_was_pressed)
        {
            button_6_was_pressed = true;
            PORTD ^= _BV(PD5);
        }
        
        // check whether button was released
        if (bit_is_clear(PINC, PC4) && button_6_was_pressed)
        {
            button_6_was_pressed = false;
        }

        /* Button B9 */
        // check whether button was pressed
        if (bit_is_set(PINC, PC5) && !button_9_was_pressed)
        {
            button_9_was_pressed = true;
            PORTB ^= _BV(PB0);
        }
        
        // check whether button was released
        if (bit_is_clear(PINC, PC5) && button_9_was_pressed)
        {
            button_9_was_pressed = false;
        }

        /* Disable column 3 (buttons: B3, B6, B9) */
        PORTC &= ~_BV(PC2);
}

int main(void)
{
    init_pins();

    while (true)
    {
        check_column_147();
        check_column_258();
        check_column_369();

        // simpliest software debounce
        _delay_ms(15);
    }
}
