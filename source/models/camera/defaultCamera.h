#ifndef SOURCE_MODELS_CAMERA_DEFAULTCAMERA_H_
#define SOURCE_MODELS_CAMERA_DEFAULTCAMERA_H_

#include "../../utils/math/math.h"
#include "camera.h"

class DefaultCamera: public Camera {
    protected:
        vec3 center;
        vec3 direction;
        vec3 up;
        vec3 left;
        float yaw;
        float pitch;
    public:
        explicit DefaultCamera(CoordinateSystem* player, vec3 center);
        ~DefaultCamera();
        virtual void increment_yaw(float dYaw);
        virtual void increment_pitch(float dPitch);
        virtual float get_yaw();
        virtual float get_pitch();
        virtual void activate();
        virtual void update();
        virtual void set_player_angles();
};

#endif  // SOURCE_MODELS_CAMERA_DEFAULTCAMERA_H_
