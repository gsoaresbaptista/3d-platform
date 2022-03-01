#ifndef SOURCE_CONTROLLERS_CAMERA_CAMERA_H_
#define SOURCE_CONTROLLERS_CAMERA_CAMERA_H_

#include "../../utils/math/math.h"

class Camera {
    private:
        vec3 position;
        vec3 direction;
        vec3 left;
        vec3 up;
        float movement_constant = 0.20;
        float yaw;
        float pitch;
    public:
        explicit Camera(vec3 pos);
        ~Camera();
        void activate();
        void move_left();
        void move_right();
        void move_forward();
        void move_backward();
        void increment_yaw(float dYaw);
        void increment_pitch(float dPitch);
        void update();
};

#endif  // SOURCE_CONTROLLERS_CAMERA_CAMERA_H_
