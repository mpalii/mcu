#ifndef GPIO_H_
#define GPIO_H_

#include <avr/io.h>

/**
 * @brief GPIO initialization function prototype.
 * @see gpio.c for implementation 
 * @param -
 * @return -
 */
void init_gpio(void);

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
#define BUILT_IN_LED            _PA0
#define ADC1_VCC                _PA1
#define ADC2_OHM                _PA2
#define _GPIO_UNUSED_04         _PA3
#define _GPIO_UNUSED_05         _PA4
#define _GPIO_UNUSED_06         _PA5
#define _GPIO_UNUSED_07         _PA6
#define _GPIO_UNUSED_08         _PA7

#define OHMMETER_1K             _PB0
#define OHMMETER_10K            _PB1
#define OHMMETER_100K           _PB2
#define _GPIO_UNUSED_12         _PB3
#define _GPIO_UNUSED_13         _PB4
#define _GPIO_UNUSED_14         _PB5
#define _GPIO_UNUSED_15         _PB6
#define BUTTON                  _PB7

#define LCD_PD0                 _PC0
#define LCD_PD1                 _PC1
#define LCD_PD2                 _PC2
#define LCD_PD3                 _PC3
#define LCD_PD4                 _PC4
#define LCD_PD5                 _PC5
#define LCD_PD6                 _PC6
#define LCD_PD7                 _PC7

#define _GPIO_UNUSED_25         _PD0
#define _GPIO_UNUSED_26         _PD1
#define _GPIO_UNUSED_27         _PD2
#define _GPIO_UNUSED_28         _PD3
#define LCD_RS                  _PD4
#define LCD_RW                  _PD5
#define LCD_EN                  _PD6
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
#define _gpio_set_output(GPIO)  (*_DDR_ADDRESS(GPIO) |= _GPIO_PIN_BIT(GPIO))
#define _gpio_set_input(GPIO)   (*_DDR_ADDRESS(GPIO) &= ~_GPIO_PIN_BIT(GPIO))
#define _gpio_high(GPIO)        (*_PORT_ADDRESS(GPIO) |= _GPIO_PIN_BIT(GPIO))
#define _gpio_low(GPIO)         (*_PORT_ADDRESS(GPIO) &= ~_GPIO_PIN_BIT(GPIO))
#define _gpio_toggle(GPIO)      (*_PORT_ADDRESS(GPIO) ^= _GPIO_PIN_BIT(GPIO))
#define _gpio_get_input(GPIO)   (*_PIN_ADDRESS(GPIO) & _GPIO_PIN_BIT(GPIO))

#endif /* GPIO_H_ */