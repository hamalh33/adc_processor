#include "adc.h"


float raw_to_voltage(uint16_t raw_value) {
    return (raw_value / 4095.0f) * 3.3f;
}


int count_overvoltage(ADCSample samples[], int count) {
    int faults = 0;
    for (int i = 0; i < count; i++) {
        float voltage = raw_to_voltage(samples[i].raw_value);
        if (voltage > 3.0f) {
            faults++;
        }
    }
    return faults;
}


int count_undervoltage(ADCSample samples[], int count) {
    int faults = 0;
    for (int i = 0; i < count; i++) {
        float voltage = raw_to_voltage(samples[i].raw_value);
        if (voltage < 0.3f) {
            faults++;
        }
    }
    return faults;
}


int count_flag_faults(ADCSample samples[], int count) {
    int faults = 0;
    for (int i = 0; i < count; i++) {
        if (samples[i].status_flags & 0x01) {
            faults++;
        }
    }
    return faults;
}