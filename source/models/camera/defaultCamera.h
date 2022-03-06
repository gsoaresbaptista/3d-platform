#ifndef SOURCE_MODELS_CAMERA_DEFAULTCAMERA_H_
#define SOURCE_MODELS_CAMERA_DEFAULTCAMERA_H_

#include "../../utils/math/math.h"
#include "camera.h"

class DefaultCamera: public Camera {
    private:
        vec3 center;
        float yaw;
        float pitch;
    public:
        explicit DefaultCamera(CoordinateSystem* player, vec3 center);
        ~DefaultCamera();
        void increment_yaw(float dYaw);
        void increment_pitch(float dPitch);
        float get_yaw();
        float get_pitch();
        void activate();
        void update();
};

#endif  // SOURCE_MODELS_CAMERA_DEFAULTCAMERA_H_
