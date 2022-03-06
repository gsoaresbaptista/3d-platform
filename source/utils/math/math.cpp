#include <cmath>
#include "math.h"

float random_float(float min, float max) {
    float r = (float)rand() / (float)RAND_MAX;
    return min + r * (max - min);
}

float distance(float num_a, float num_b) {
    return sqrt(pow(num_a - num_b, 2));
}
