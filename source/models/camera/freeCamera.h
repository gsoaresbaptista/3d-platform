#ifndef SOURCE_MODELS_CAMERA_FREECAMERA_H_
#define SOURCE_MODELS_CAMERA_FREECAMERA_H_

#include "../../utils/others/SVGReader.h"
#include "../../utils/math/math.h"
#include "camera.h"

class FreeCamera : public Camera {
    private:
        vec3 position;
        vec3 direction;
        vec3 left;
        vec3 up;
        GLfloat block_size;
        vec3 center;

        std::shared_ptr<SVGData> data;
        float yaw;
        float pitch;
    public:
        FreeCamera(
            CoordinateSystem* player, vec3 center,
            std::shared_ptr<SVGData> data, GLfloat block_size);
        ~FreeCamera();
        void activate();
        void update();
        void increment_yaw(float dYaw);
        void increment_pitch(float dPitch);
};

#endif  // SOURCE_MODELS_CAMERA_FREECAMERA_H_
