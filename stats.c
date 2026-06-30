#include "stats.h"
#include <math.h>

float average(float values[], int count) {
    float sum = 0;
    for (int i = 0; i < count; i++) {
        sum = sum + values[i];
    }
    return sum / count;
}

float find_min(float values[], int count) {
    float min = values[0];
    for (int i = 1; i < count; i++) {
        if (values[i] < min) {
            min = values[i];
        }
    }
    return min;
}

float find_max(float values[], int count) {
    float max = values[0];
    for (int i = 1; i < count; i++) {
        if (values[i] > max) {
            max = values[i];
        }
    }
    return max;
}


float standard_deviation(float values[], int count) {
    float avg = average(values, count);
    float sum = 0;
    for (int i = 0; i < count; i++) {
        float diff = values[i] - avg;
        sum = sum + (diff * diff);
    }
    return sqrt(sum / count);
}