#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>

void init_adc(void);
uint16_t adc_get_conversion_result(void);

#endif /* ADC_H_ */