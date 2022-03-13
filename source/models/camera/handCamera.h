#ifndef SOURCE_MODELS_CAMERA_HANDCAMERA_H_
#define SOURCE_MODELS_CAMERA_HANDCAMERA_H_

#include "../../utils/math/math.h"
#include "defaultCamera.h"
#include <GL/glu.h>

class HandCamera: public DefaultCamera {
    private:
        float block_size;

    public:
        explicit HandCamera(CoordinateSystem* player, vec3 center, float block_size)
            : DefaultCamera(player, center) { this->block_size = block_size; }
        ~HandCamera();

        void update();
        void activate();
        void set_player_angles();
};

#endif  // SOURCE_MODELS_CAMERA_HANDCAMERA_H_
