#ifndef SOURCE_UTILS_LINEAR_VEC2_H_
#define SOURCE_UTILS_LINEAR_VEC2_H_

#include <GL/gl.h>

struct vec2 {
    GLfloat x;
    GLfloat y;

    vec2() : x(0), y(0) {}
    vec2(GLfloat x_, GLfloat y_) : x(x_), y(y_) {}
};

#endif  // SOURCE_UTILS_LINEAR_VEC2_H_
