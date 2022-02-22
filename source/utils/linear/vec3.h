#ifndef SOURCE_UTILS_LINEAR_VEC3_H_
#define SOURCE_UTILS_LINEAR_VEC3_H_

#include <GL/gl.h>

struct vec3 {
    GLfloat x;
    GLfloat y;
    GLfloat z;

    vec3() : x(0), y(0), z(0) {}
    vec3(GLfloat x_, GLfloat y_, GLfloat z_) : x(x_), y(y_), z(z_){}
};

#endif  // SOURCE_UTILS_LINEAR_VEC3_H_
