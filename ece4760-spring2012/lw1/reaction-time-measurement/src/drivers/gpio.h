#ifndef GPIO_H_
#define GPIO_H_

/*
 * General purpose IO pins assignment and handling
 * ATmega644 has 32 general purpose IO lines
 * Four 8bit ports (A, B, C, and D)
 */

#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>

/*
 * Generic pin map table
 */
#define _PA0                    (0U)
#define _PA1                    (1U)
#define _PA2                    (2U)
#define _PA3                    (3U)
#define _PA4                    (4U)
#define _PA5                    (5U)
#define _PA6                    (6U)
#define _PA7                    (7U)

#define _PB0                    (8U)
#define _PB1                    (9U)
#define _PB2                    (10U)
#define _PB3                    (11U)
#define _PB4                    (12U)
#define _PB5                    (13U)
#define _PB6                    (14U)
#define _PB7                    (15U)

#define _PC0                    (16U)
#define _PC1                    (17U)
#define _PC2                    (18U)
#define _PC3                    (19U)
#define _PC4                    (20U)
#define _PC5                    (21U)
#define _PC6                    (22U)
#define _PC7                    (23U)

#define _PD0                    (24U)
#define _PD1                    (25U)
#define _PD2                    (26U)
#define _PD3                    (27U)
#define _PD4                    (28U)
#define _PD5                    (29U)
#define _PD6                    (30U)
#define _PD7                    (31U)

/*
 * Hardware pin mapping
 */
#define LED                     _PA0
#define _GPIO_UNUSED_02         _PA1
#define _GPIO_UNUSED_03         _PA2
#define _GPIO_UNUSED_04         _PA3
#define _GPIO_UNUSED_05         _PA4
#define _GPIO_UNUSED_06         _PA5
#define _GPIO_UNUSED_07         _PA6
#define _GPIO_UNUSED_08         _PA7

#define _GPIO_UNUSED_09         _PB0
#define _GPIO_UNUSED_10         _PB1
#define _GPIO_UNUSED_11         _PB2
#define _GPIO_UNUSED_12         _PB3
#define _GPIO_UNUSED_13         _PB4
#define _GPIO_UNUSED_14         _PB5
#define _GPIO_UNUSED_15         _PB6
#define _GPIO_UNUSED_16         _PB7

#define _GPIO_UNUSED_17         _PC0
#define _GPIO_UNUSED_18         _PC1
#define _GPIO_UNUSED_19         _PC2
#define _GPIO_UNUSED_20         _PC3
#define _GPIO_UNUSED_21         _PC4
#define _GPIO_UNUSED_22         _PC5
#define _GPIO_UNUSED_23         _PC6
#define _GPIO_UNUSED_24         _PC7

#define _GPIO_UNUSED_25         _PD0
#define _GPIO_UNUSED_26         _PD1
#define _GPIO_UNUSED_27         _PD2
#define _GPIO_UNUSED_28         _PD3
#define _GPIO_UNUSED_29         _PD4
#define _GPIO_UNUSED_30         _PD5
#define _GPIO_UNUSED_31         _PD6
#define _GPIO_UNUSED_32         _PD7

/*
 * Addresses of DDRx, PORTx and PINx registers have the same offset and equals to 3.
 * It is useful for determining a real register address during a bit manipulation
 * 
 * PINA:0x00;  PINB:Ox03;  PINC:0x06;  PIND:0x09     -> offset = 3U
 * DDRA:0x01;  DDRB:0x04;  DDRC:0x07;  DDRD:0x0a     -> offset = 3U
 * PORTA:0x02; PORTB:0x05; PORTC:0x08; PORTD:0x0b    -> offset = 3U
 * 
 * Port A will be a starting point for determining adresses of direction, port, and pin registers for other ports (B, C, and D)
 */
#define _SFR_OFFSET             (3U)
#define _INIT_DDR_ADDRESS       (&DDRA)
#define _INIT_PORT_ADDRESS      (&PORTA)
#define _INIT_PIN_ADDRESS       (&PINA)

/*
 * The main idea is that every value from generic pin map table represents two values: 
 * - pin number (0b00000111 a.k.a 7U mask); 
 * - port number (0b00011000 a.k.a. 3U << 3U, or 3U << GPIO_PORT_OFFSET).
 * 
 * Port number * SFR_OFFSET gives offset for determining the real register address. 
 * It depends on initial DDR, PORT, and PIN addresses.
 */
#define _GPIO_PORT_OFFSET       (3U)
#define _GPIO_PORT_MASK         (3U << _GPIO_PORT_OFFSET)
#define _GPIO_PIN_MASK          (7U)

/*
 * Macro for extracting the physical (hardware) bit value from generic pin value
 */
#define _GPIO_PIN_BIT(GPIO)     (1 << (GPIO & _GPIO_PIN_MASK))

/*
 * Macro for extracting the port number from the generic pin value
 */
#define _GPIO_PORT(GPIO)        ((GPIO & _GPIO_PORT_MASK) >> _GPIO_PORT_OFFSET)

#define _DDR_ADDRESS(GPIO)      (_INIT_DDR_ADDRESS + (_GPIO_PORT(GPIO) * _SFR_OFFSET))
#define _PORT_ADDRESS(GPIO)     (_INIT_PORT_ADDRESS + (_GPIO_PORT(GPIO) * _SFR_OFFSET))
#define _PIN_ADDRESS(GPIO)      (_INIT_PIN_ADDRESS + (_GPIO_PORT(GPIO) * _SFR_OFFSET))

// GPIO state manipulation macroses
#define gpio_set_output(GPIO)   (*_DDR_ADDRESS(GPIO) |= _GPIO_PIN_BIT(GPIO))
#define gpio_set_input(GPIO)    (*_DDR_ADDRESS(GPIO) &= ~_GPIO_PIN_BIT(GPIO))
#define gpio_high(GPIO)         (*_PORT_ADDRESS(GPIO) |= _GPIO_PIN_BIT(GPIO))
#define gpio_low(GPIO)          (*_PORT_ADDRESS(GPIO) &= ~_GPIO_PIN_BIT(GPIO))
#define gpio_toggle(GPIO)       (*_PORT_ADDRESS(GPIO) ^= _GPIO_PIN_BIT(GPIO))
#define gpio_get_input(GPIO)    (*_PIN_ADDRESS(GPIO) & _GPIO_PIN_BIT(GPIO))

void init_gpio(void)
{
    /**
     * @def disable JTAG interface in order to make pins 2, 3, 4, 5 (Port C) as general purpose
     * @see https://ww1.microchip.com/downloads/en/DeviceDoc/doc2593.pdf#G1.1375224
     */
    MCUCR |= _BV(JTD);
    MCUCR |= _BV(JTD);

    // Main pin configuration
    /* TODO */

    // Turn on built in led
    gpio_set_output(LED);
}

#endif /* GPIO_H_ */