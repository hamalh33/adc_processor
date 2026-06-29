#include <stdio.h>
#include "adc.h"
#include <stdlib.h>


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
        printf("Error: wrong file (invalid magic number)\n");
        fclose(file);
        return 1;
    }

    printf("Magic: %x\n", header.magic);
    printf("Version: %u\n", header.version);
    printf("Channels: %u\n", header.channel_count);
    printf("Records: %u\n", header.record_count);

ADCSample *samples = malloc(header.record_count * sizeof(ADCSample));
    if (samples == NULL) {
        printf("Error allocating samples\n");
        fclose(file);
        return 1;
    }

    fread(samples,sizeof(ADCSample),header.record_count,file);
    printf("first sample: channel=%u raw=%u\n", samples[0].channel_id, samples[0].raw_value);

    free(samples);
    fclose(file);
    return 0;


}



