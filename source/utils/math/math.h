#ifndef SOURCE_UTILS_MATH_MATH_H_
#define SOURCE_UTILS_MATH_MATH_H_

#include <stdlib.h>
#include "vec2.h"
#include "vec3.h"

float random_float(float min, float max);
float distance(float num_a, float num_b);
float distance_xz(vec3 a, vec3 b);

#endif  // SOURCE_UTILS_MATH_MATH_H_
