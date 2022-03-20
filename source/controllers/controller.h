#ifndef SOURCE_CONTROLLERS_CONTROLLER_H_
#define SOURCE_CONTROLLERS_CONTROLLER_H_

#include <memory>
#include "keyboardListener.h"
#include "mouseListener.h"
#include "../utils/math/math.h"
#include "controllerData.h"

class Controller {
    public:
        static std::shared_ptr<ControllerData> registerCallbacks() {
            std::shared_ptr<ControllerData> data =
                std::make_shared<ControllerData>();

            data->to_rotate = vec3(0, 0, 0);
            data->mouse_delta = vec2(0, 0);
            data->night_mode = false;
            data->left_mouse_button = false;
            data->right_mouse_button = false;
            data->move_orbital_camera = false;
            data->disable_mouse_warp = false;
            data->mouse_sensitivity = 3;
            data->night_mode = false;

            for (int i = 0; i < 256; i++)
                data->keys[i] = false;

            // Listeners
            KeyboardListener::registerCallbacks(data);
            MouseListener::registerCallbacks(data);

            return data;
        }
};

#endif  // SOURCE_CONTROLLERS_CONTROLLER_H_
