#ifndef SOURCE_CONTROLLERS_MOUSELISTENER_H_
#define SOURCE_CONTROLLERS_MOUSELISTENER_H_

#include "../utils/math/math.h"
#include "controllerData.h"
#include <memory>
#include "../models/camera/defaultCamera.h"

class MouseListener {
    public:
        static void registerCallbacks(std::shared_ptr<ControllerData> data);
        static void set_camera(DefaultCamera* camera);
};

#endif  // SOURCE_CONTROLLERS_MOUSELISTENER_H_
