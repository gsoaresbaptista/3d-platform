#ifndef SOURCE_CONTROLLERS_CONTROLLERDATA_H_
#define SOURCE_CONTROLLERS_CONTROLLERDATA_H_

#include "../utils/math/math.h"

struct ControllerData {
    vec3 to_translate;
    vec3 to_rotate;
    GLuint keys[256];
};

#endif  // SOURCE_CONTROLLERS_CONTROLLERDATA_H_
