#include "i2c.h"
#include "gpio.h"

/****************************************************************************/
/* Set up SCL frequency                                                     */
/* CPU Clock frequency / (16 + 2 * [TWBR] * [4 pow(TWPS)])                  */
/* 16_000_000 Hz / (16 + 2 * [2] * [16]) = 200_000 Hz                       */
/****************************************************************************/
void init_i2c(void)
{
    // TWI Bit Rate Register
    TWBR = 2;
    // Prescaler Value 4
    TWSR |= _BV(TWPS0);
}

void i2c_start(void)
{
    // TWI Control Register
    TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);
    // Wait untill TWINT is set
    loop_until_bit_is_set(TWCR, TWINT);
}

void i2c_continue_no_ack(void)
{
    // TWI Control Register
    TWCR = _BV(TWINT) | _BV(TWEN);
    // Wait untill TWINT is set
    loop_until_bit_is_set(TWCR, TWINT);
}

void i2c_continue_ack(void)
{
    // TWI Control Register
    TWCR = _BV(TWEA) | _BV(TWINT) | _BV(TWEN);
    // Wait untill TWINT is set
    loop_until_bit_is_set(TWCR, TWINT);
}

void i2c_stop(void)
{
    // TWI Control Register
    TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN);
}

uint8_t i2c_get_status(void)
{
    // TWI Status Register
    return TWSR & 0xF8; // aka 0b11111000 
}

uint8_t i2c_get_data(void)
{
    // TWI Data Register
    return TWDR;
}

void i2c_set_data(uint8_t data)
{
    // TWI Data Register
    TWDR = data; 
}
