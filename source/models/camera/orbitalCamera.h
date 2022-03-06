#ifndef SOURCE_MODELS_CAMERA_ORBITALCAMERA_H_
#define SOURCE_MODELS_CAMERA_ORBITALCAMERA_H_

#include "../../utils/math/math.h"
#include "camera.h"

class OrbitalCamera: public Camera {
    private:
        vec3 center;
        vec3 position;
        vec3 look;
        float radius;
        float phi;
        float theta;
        float block_size;

        //
        vec3 cvt2cartesian();

    public:
        explicit OrbitalCamera(
            CoordinateSystem* player,
            vec3 center, float block_size);
        ~OrbitalCamera();
        void increment_theta(float delta_theta);
        void increment_phi(float delta_phi);
        void zoom_in();
        void zoom_out();
        void activate();
        void update();
};

#endif  // SOURCE_MODELS_CAMERA_ORBITALCAMERA_H_
