#ifndef SOURCE_MODELS_CAMERA_CAMERA_H_
#define SOURCE_MODELS_CAMERA_CAMERA_H_

#include "../../utils/math/math.h"
#include "../player.h"

class Camera {
    protected:
        CoordinateSystem* player;
    public:
        explicit Camera(CoordinateSystem* player);
        ~Camera();
        virtual void activate() = 0;
        virtual void update() = 0;
};

#endif  // SOURCE_MODELS_CAMERA_CAMERA_H_
