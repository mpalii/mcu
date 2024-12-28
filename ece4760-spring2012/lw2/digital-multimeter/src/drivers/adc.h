#ifndef ADC_H_
#define ADC_H_

#define ADC_CHANNEL_0   (0)
#define ADC_CHANNEL_1   (1)
#define ADC_CHANNEL_2   (2)
#define ADC_CHANNEL_3   (3)
#define ADC_CHANNEL_4   (4)
#define ADC_CHANNEL_5   (5)
#define ADC_CHANNEL_6   (6)
#define ADC_CHANNEL_7   (7)

#define INTERNAL_VOLTAGE_REFERENCE_1_10_MV  (1085UL)    // VC61A 2V
#define INTERNAL_VOLTAGE_REFERENCE_2_56_MV  (2520UL)    // VC61A 20V

#define VOLTAGE_DIVIDER_RESISTOR_1_HOHM     (98UL)      // VC61A 200k
#define VOLTAGE_DIVIDER_RESISTOR_2_HOHM     (45UL)      // VC61A 200k
#define VOLTAGE_DIVIDER_IMPEDANCE           (VOLTAGE_DIVIDER_RESISTOR_1_HOHM + VOLTAGE_DIVIDER_RESISTOR_2_HOHM)

#define R_INT_1KOHM                         (30UL)
#define R_1KOHM                             (997UL)     // VC61A 2k
#define OHMMETER_1KOHM                      (R_1KOHM + R_INT_1KOHM)

#define R_INT_10KOHM                        (42UL)      // aka 42.7 ohm
#define R_10KOHM                            (9830UL)   // VC61A 20k
#define OHMMETER_10KOHM                     (R_10KOHM + R_INT_10KOHM)

void init_adc(void);
void set_alt_adc_channel(uint8_t);
uint16_t get_vcc_conversion_result(void);
uint16_t get_alt_conversion_result(void);


#endif /* ADC_H_ */