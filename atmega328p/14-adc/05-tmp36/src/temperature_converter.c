#include "temperature_converter.h"

int16_t convert_as_decicelsius(uint16_t voltage_level)
{
    return (voltage_level - 500);
}