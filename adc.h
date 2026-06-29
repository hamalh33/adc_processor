#ifndef ADC_H
#define ADC_H

#include <stdint.h>

#pragma pack(push, 1)
typedef struct {
    uint32_t magic;
    uint16_t version;
    uint16_t channel_count;
    uint32_t record_count;
    uint32_t sample_rate;
    uint8_t reserved[8];
}ADCHeader;
#pragma pack(pop)




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