#include "stats.h"

float average(float values[], int count) {
    float sum = 0;
    for (int i = 0; i < count; i++) {
        sum = sum + values[i];
    }
    return sum / count;
}