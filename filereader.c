#include <stdio.h>
#include "adc.h"

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


    fclose(file);
    return 0;


}



