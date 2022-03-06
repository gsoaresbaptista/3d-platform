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
        std::shared_ptr<SVGData> data;
    public:
        FreeCamera(
            CoordinateSystem* player,
            std::shared_ptr<SVGData> data, GLfloat block_size);
        ~FreeCamera();
        void activate();
        void update();
};

#endif  // SOURCE_MODELS_CAMERA_FREECAMERA_H_
