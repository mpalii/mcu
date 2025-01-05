#include <stdint.h>
#include <stdio.h>
#include "drivers/adc.h"
#include "drivers/gpio.h"
#include "drivers/lcd.h"
#include "system/events.h"
#include "system/state_machine.h"

char text_buffer_lcd_4[33]            = { 0 };

e_state handle_res_100k_measuring(void)
{
    if (button_event)
    {
        button_event = false;
        // disable ohmmeter 100k power line
        _gpio_low(OHMMETER_100K);
        _gpio_set_input(OHMMETER_100K);

        lcd_add_to_rendering("\b");
        return VCC_MEASURING;
    }

    uint16_t vcc_conversion_result = get_vcc_conversion_result();
    uint16_t alt_conversion_result = get_alt_conversion_result();

    if (alt_conversion_result > 999)
    {
        sprintf(text_buffer_lcd_4, "\r3.Ohmmeter 100k\xF4\n%04u:%04u  HIGH\xF4", vcc_conversion_result, alt_conversion_result);
        lcd_add_to_rendering(text_buffer_lcd_4);

        return RES_MEASURING_100K;
    }

    float vcc_mv = map_to_millivolts(vcc_conversion_result) * VOLTAGE_DIVIDER_IMPEDANCE / VOLTAGE_DIVIDER_RESISTOR_2_HOHM;
    float alt_mv = map_to_millivolts(alt_conversion_result);

    float dif_mv = vcc_mv - alt_mv;
    uint16_t resistance = (uint16_t) ((OHMMETER_100KOHM * alt_mv) / dif_mv);
    resistance /= 10;

    sprintf(text_buffer_lcd_4, "\r3.Ohmmeter 100k\xF4\n%04u:%04u %3u.%1uk", vcc_conversion_result, alt_conversion_result, resistance / 10, resistance % 10);
    lcd_add_to_rendering(text_buffer_lcd_4);

    return RES_MEASURING_100K;
}