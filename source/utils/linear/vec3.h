#ifndef SOURCE_UTILS_LINEAR_VEC3_H_
#define SOURCE_UTILS_LINEAR_VEC3_H_

#include <GL/gl.h>

struct vec3 {
    GLfloat x;
    GLfloat y;
    GLfloat z;

    vec3() : x(0), y(0), z(0) {}
    vec3(GLfloat x_, GLfloat y_, GLfloat z_) : x(x_), y(y_), z(z_) {}

    vec3 operator+(const vec3& v) const {
        return vec3(x + v.x, y + v.y, z + v.z);
    }

    vec3 operator*(const float k) const {
        return vec3(x*k, y*k, z*k);
    }
};

#endif  // SOURCE_UTILS_LINEAR_VEC3_H_
