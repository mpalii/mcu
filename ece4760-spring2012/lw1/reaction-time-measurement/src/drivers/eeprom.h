#ifndef EEPROM_H_
#define EEPROM_H_

#include <stdint.h>

void eeprom_save_score(uint16_t score);
void eeprom_write_score(void);

#endif /* EEPROM_H_ */