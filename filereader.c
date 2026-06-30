#include <stdio.h>
#include <stdlib.h>
#include "adc.h"
#include "stats.h"


int main(int argc, char *argv[]) {
   if (argc != 2) {
       printf("usage: %s <filename>\n", argv[0]);
       return 1;
   }


    FILE *file = fopen(argv[1], "rb");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }


    ADCHeader header;
    fread(&header,sizeof(ADCHeader),1, file);

    if (header.magic != 0xADC1BEEF) {
        printf("Error: invalid file (wrong magic number)\n");
        fclose(file);
        return 1;
    }

    printf("Magic: %x\n", header.magic);
    printf("Version: %u\n", header.version);
    printf("Channels: %u\n", header.channel_count);
    printf("Records: %u\n", header.record_count);

ADCSample *samples = malloc(header.record_count * sizeof(ADCSample));
    if (samples == NULL) {
        printf("Error: could not allocate memory\n");
        fclose(file);
        return 1;
    }

    fread(samples,sizeof(ADCSample),header.record_count,file);
    printf("first sample: channel=%u raw=%u\n", samples[0].channel_id, samples[0].raw_value);
    printf("first sample voltage: %f\n", raw_to_voltage(samples[0].raw_value));
    printf("overvoltage faults: %d\n", count_overvoltage(samples, header.record_count));
    printf("undervoltage faults: %d\n", count_undervoltage(samples, header.record_count));
    printf("flag faults: %d\n", count_flag_faults(samples, header.record_count));
    printf("sequence gaps: %d\n", count_sequence_gaps(samples, header.record_count));
    FILE *out = fopen("results.txt", "w");
    fprintf(out, "ADC analysis results\n");
    fprintf(out, "records: %u\n", header.record_count);
    fprintf(out, "overvoltage faults: %d\n", count_overvoltage(samples, header.record_count));
    fprintf (out, "undervoltage faults: %d\n", count_undervoltage(samples, header.record_count));
    fprintf(out, "flag faults: %d\n", count_flag_faults(samples, header.record_count));
    fprintf(out, "sequence gaps: %d\n", count_sequence_gaps(samples, header.record_count));


for (int ch = 0; ch < header.channel_count; ch++) {
    float voltage[1000];
    int count = 0;
    for (int i = 0; i < header.record_count; i++) {
        if (samples[i].channel_id == ch) {
            voltage[count] = raw_to_voltage(samples[i].raw_value);
            count++;
        }
    }
    printf("channel %d average voltage: %f\n", ch, average(voltage, count));
    printf("channel %d min voltage: %f\n", ch, find_min(voltage, count));
    printf("channel %d max voltage: %f\n", ch, find_max(voltage, count));
    printf("channel %d standard dev: %f\n", ch, standard_deviation(voltage, count));
    fprintf(out, "channel %d: avg=%f min=%f max=%f std=%f\n", ch, average(voltage, count),find_min(voltage, count), find_max(voltage, count), standard_deviation(voltage, count));

}

    free(samples);
    fclose(file);
    fclose(out);
    return 0;


}