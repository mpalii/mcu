#include <stdint.h>
#include <stdio.h>
#include "drivers/adc.h"
#include "drivers/gpio.h"
#include "drivers/lcd.h"
#include "system/events.h"
#include "system/state_machine.h"

char text_buffer_lcd_2[33]            = { 0 };

e_state handle_res_1k_measuring(void)
{
    if (button_event)
    {
        button_event = false;
        // disable ohmmeter 1k power line
        _gpio_low(OHMMETER_1K);
        _gpio_set_input(OHMMETER_1K);
        // enable ohmmeter 10k power line
        _gpio_set_output(OHMMETER_10K);
        _gpio_high(OHMMETER_10K);

        lcd_add_to_rendering("\b");
        return RES_MEASURING_10K;
    }

    uint16_t vcc_conversion_result = get_vcc_conversion_result();
    uint16_t alt_conversion_result = get_alt_conversion_result();

    if (alt_conversion_result > 999)
    {
        sprintf(text_buffer_lcd_2, "\r1.Ohmmeter 1k\xF4\n%04u:%04u  HIGH\xF4", vcc_conversion_result, alt_conversion_result);
        lcd_add_to_rendering(text_buffer_lcd_2);

        return RES_MEASURING_1K;
    }

    uint16_t vcc_mv = (((uint32_t) vcc_conversion_result * 10 + ADC_OFFSET_CORRECTION) * INTERNAL_VOLTAGE_REFERENCE_2_56_MV * VOLTAGE_DIVIDER_IMPEDANCE) / (((uint32_t) 10240) * VOLTAGE_DIVIDER_RESISTOR_2_HOHM);
    uint16_t alt_mv = (((uint32_t) alt_conversion_result * 10 + ADC_OFFSET_CORRECTION) * INTERNAL_VOLTAGE_REFERENCE_2_56_MV) / ((uint32_t) 10240);

    uint16_t dif_mv = vcc_mv - alt_mv;
    uint16_t resistance = (((uint32_t) OHMMETER_1KOHM) * alt_mv) / dif_mv;

    sprintf(text_buffer_lcd_2, "\r1.Ohmmeter 1k\xF4\n%04u:%04u  %4u\xF4", vcc_conversion_result, alt_conversion_result, resistance);
    lcd_add_to_rendering(text_buffer_lcd_2);

    return RES_MEASURING_1K;
}