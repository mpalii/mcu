#ifndef _CUSTOM_DELAY_H_
#define _CUSTOM_DELAY_H_ 1
// BEGIN


#ifndef FREQUENCY
# warning "FREQUENCY not defined for "frequency.h">"
# define FREQUENCY 1
#endif


#if ((FREQUENCY == 1) || (FREQUENCY == 24) || (FREQUENCY == 50) || (FREQUENCY == 240))
    #include <util/delay.h>
    const double HALF_PERIOD = F_CPU / (2.0 * FREQUENCY);
#else
    # warning "FREQUENCY should be specified as 1, 24, 50 or 240 hertz>"
    #error "FREQUENCY value ERROR"
#endif


void _delay_with_frequency(void) {
    _delay_us(HALF_PERIOD);
}


// END
#endif /* _CUSTOM_DELAY_H_ */
