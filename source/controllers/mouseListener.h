#ifndef SOURCE_CONTROLLERS_MOUSELISTENER_H_
#define SOURCE_CONTROLLERS_MOUSELISTENER_H_

#include "../utils/math/math.h"
#include "controllerData.h"
#include <memory>
#include "../models/camera/defaultCamera.h"
#include "../models/camera/orbitalCamera.h"

class MouseListener {
    public:
        static void registerCallbacks(std::shared_ptr<ControllerData> data);
        static void set_camera(DefaultCamera* camera);
        static void set_camera(OrbitalCamera* camera);
        static void clear_camera();
};

#endif  // SOURCE_CONTROLLERS_MOUSELISTENER_H_
