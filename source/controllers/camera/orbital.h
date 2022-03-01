#ifndef SOURCE_CONTROLLERS_CAMERA_ORBITAL_H_
#define SOURCE_CONTROLLERS_CAMERA_ORBITAL_H_

#include <GL/gl.h>
#include <cmath>
#include "../../utils/math/math.h"

class Orbital {
    private:
        float radius;
        float phi;
        float theta;
        vec3 position;
        vec3 look;

    public:
        Orbital(float radius, float theta, float phi);
        ~Orbital();
        void activate();
        void forward();
        void backward();
        void update_theta(float delta_theta);
        void update_phi(float delta_phi);

    private:
        vec3 cvt2cartesian();
        void update();
};

#endif  // SOURCE_CONTROLLERS_CAMERA_ORBITAL_H_
