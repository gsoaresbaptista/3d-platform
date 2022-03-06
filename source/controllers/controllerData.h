#ifndef SOURCE_CONTROLLERS_CONTROLLERDATA_H_
#define SOURCE_CONTROLLERS_CONTROLLERDATA_H_

#include "../utils/math/math.h"

struct ControllerData {
    vec3 to_rotate;
    vec2 mouse_delta;
    GLuint keys[256];
    GLboolean move_orbital_camera;
};

#endif  // SOURCE_CONTROLLERS_CONTROLLERDATA_H_
