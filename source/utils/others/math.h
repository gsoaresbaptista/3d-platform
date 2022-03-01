#ifndef SOURCE_UTILS_OTHERS_MATH_H_
#define SOURCE_UTILS_OTHERS_MATH_H_

float random_float(float min, float max) {
    float r = (float)rand() / (float)RAND_MAX;
    return min + r * (max - min);
}

#endif  // SOURCE_UTILS_OTHERS_MATH_H_
