#ifndef ONEWIRE_H_
#define ONEWIRE_H_

#define F_CPU (8000000UL)

// onewire bus commands
#define CMD_READ_ROM        (0x33)

#include <stdbool.h>
#include <util/delay.h>

bool onewire_reset(void);
void onewire_write(uint8_t byte);
uint8_t onewire_read(void);

#endif /* ONEWIRE_H_ */