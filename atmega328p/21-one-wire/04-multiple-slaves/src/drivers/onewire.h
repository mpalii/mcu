#ifndef ONEWIRE_H_
#define ONEWIRE_H_

#define F_CPU (8000000UL)

// onewire bus commands
#define CMD_READ_ROM            (0x33)
#define CMD_SKIP_ROM            (0xCC)
#define CMD_CONVERT_T           (0x44)
#define CMD_READ_SCRATCHPAD     (0xBE)
#define CMD_MATCH_ROM           (0x55)

#include <stdbool.h>
#include <util/delay.h>

bool onewire_reset(void);
void onewire_write(uint8_t byte);
uint8_t onewire_read(void);

#endif /* ONEWIRE_H_ */