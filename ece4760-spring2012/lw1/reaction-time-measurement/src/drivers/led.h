#ifndef LED_H_
#define LED_H_

#include <stdbool.h>

void init_led(void);
void led_on(void);
void led_off(void);
bool led_toggle_enable_flag(void);

#endif /* LED_H_ */