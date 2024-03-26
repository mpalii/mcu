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

void handle_button(volatile uint8_t * pin_port, uint8_t pin, bool * button_was_pressed, volatile uint8_t * port_led, uint8_t pin_led)
{
    // check whether button was pressed
    if (bit_is_set(*pin_port, pin) && !(*button_was_pressed))
    {
        *button_was_pressed = true;
        *port_led ^= _BV(pin_led);
    }
    
    // check whether button was released
    if (bit_is_clear(*pin_port, pin) && *button_was_pressed)
    {
        *button_was_pressed  = false;
    }
}

static inline void check_column_147(void)
{
        /* Enable column 1 (buttons: B1, B4, B7) */
        PORTC |= _BV(PC0);
        
        /* Button B1 */
        handle_button(&PINC, PC3, &button_1_was_pressed, &PORTD, PD0);
        /* Button B4 */
        handle_button(&PINC, PC4, &button_4_was_pressed, &PORTD, PD3);
        /* Button B7 */
        handle_button(&PINC, PC5, &button_7_was_pressed, &PORTD, PD6);

        /* Disable column 1 (buttons: B1, B4, B7) */
        PORTC &= ~_BV(PC0);
}

static inline void check_column_258(void)
{
        /* Enable column 2 (buttons: B2, B5, B8) */
        PORTC |= _BV(PC1);
        
        /* Button B2 */
        handle_button(&PINC, PC3, &button_2_was_pressed, &PORTD, PD1);
        /* Button B5 */
        handle_button(&PINC, PC4, &button_5_was_pressed, &PORTD, PD4);
        /* Button B8 */
        handle_button(&PINC, PC5, &button_8_was_pressed, &PORTD, PD7);

        /* Disable column 1 (buttons: B2, B5, B8) */
        PORTC &= ~_BV(PC1);
}

static inline void check_column_369(void)
{
        /* Enable column 3 (buttons: B3, B6, B9) */
        PORTC |= _BV(PC2);
        
        /* Button B3 */
        handle_button(&PINC, PC3, &button_3_was_pressed, &PORTD, PD2);
        /* Button B6 */
        handle_button(&PINC, PC4, &button_6_was_pressed, &PORTD, PD5);
        /* Button B9 */
        handle_button(&PINC, PC5, &button_9_was_pressed, &PORTB, PB0);

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
