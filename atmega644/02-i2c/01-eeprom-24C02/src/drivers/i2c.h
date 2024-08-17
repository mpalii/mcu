#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>

#define READ_BIT_MASK (0b00000001)      // use with '|'
#define WRITE_BIT_MASK (0b11111110)     // use with '&'

void init_i2c(void);
void i2c_start(void);
void i2c_continue(void);
void i2c_stop(void);
uint8_t i2c_get_status(void);
uint8_t i2c_get_data(void);
void i2c_set_data(uint8_t);

#endif /* I2C_H_ */