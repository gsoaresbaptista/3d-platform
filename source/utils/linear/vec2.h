#ifndef SOURCE_UTILS_LINEAR_VEC2_H_
#define SOURCE_UTILS_LINEAR_VEC2_H_

#include <GL/gl.h>

struct vec2 {
    GLfloat x;
    GLfloat y;

    vec2() : x(0), y(0) {}
    vec2(GLfloat x_, GLfloat y_) : x(x_), y(y_) {}

    vec2 operator+(const vec2& k) const {
        return vec2(x + k.x, y + k.y);
    }

    vec2 operator*(const float k) const {
        return vec2(x*k, y*k);
    }

    GLfloat distance(const vec2& v) {
        return sqrt(
            pow(x - v.x, 2) +
            pow(y - v.y, 2));
    }
};

#endif  // SOURCE_UTILS_LINEAR_VEC2_H_
