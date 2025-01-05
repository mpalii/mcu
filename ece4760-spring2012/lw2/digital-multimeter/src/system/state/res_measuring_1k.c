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

    float vcc_mv = map_to_millivolts(vcc_conversion_result) * VOLTAGE_DIVIDER_IMPEDANCE / VOLTAGE_DIVIDER_RESISTOR_2_HOHM;
    float alt_mv = map_to_millivolts(alt_conversion_result);

    float dif_mv = vcc_mv - alt_mv;
    uint16_t resistance = (uint16_t) ((OHMMETER_1KOHM * alt_mv) / dif_mv);

    sprintf(text_buffer_lcd_2, "\r1.Ohmmeter 1k\xF4\n%04u:%04u  %4u\xF4", vcc_conversion_result, alt_conversion_result, resistance);
    lcd_add_to_rendering(text_buffer_lcd_2);

    return RES_MEASURING_1K;
}