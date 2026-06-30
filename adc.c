#include "adc.h"


float raw_to_voltage(uint16_t raw_value) {
    return (raw_value / 4095.0f) * 3.3f;
}