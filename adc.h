#ifndef ADC_H
#define ADC_H

#include <stdint.h>

#pragma pack(push, 1)
typedef struct {
    float timestamp;
    uint8_t channel_id;
    uint16_t raw_value;
    int16_t temperature;
    uint8_t status_flags;
    uint32_t sequence_number;
    uint8_t reserved[2];
} ADCSample;
#pragma pack(pop)

#endif