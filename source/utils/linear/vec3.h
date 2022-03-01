#ifndef SOURCE_UTILS_LINEAR_VEC3_H_
#define SOURCE_UTILS_LINEAR_VEC3_H_

#include <GL/gl.h>
#include <cmath>

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

    vec3 operator*(const vec3& v) const {
        return vec3(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
    }

    vec3 operator/(const float k) const {
        return vec3(x/k, y/k, z/k);
    }

    GLfloat distance(const vec3& v) {
        return sqrt(
            pow(x - v.x, 2) +
            pow(y - v.y, 2) +
            pow(z - v.z, 2));
    }

    float magnitude() {
        return sqrt(x*x + y*y + z*z);
    }

    vec3 normalize() {
        float norm = this->magnitude();
        return vec3(x/norm, y/norm, z/norm);
    }
};

#endif  // SOURCE_UTILS_LINEAR_VEC3_H_
