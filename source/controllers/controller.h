#ifndef SOURCE_CONTROLLERS_CONTROLLER_H_
#define SOURCE_CONTROLLERS_CONTROLLER_H_

#include <memory>
#include "keyboardListener.h"
#include "../utils/math/math.h"
#include "controllerData.h"

class Controller {
    public:
        static std::shared_ptr<ControllerData> registerCallbacks() {
            std::shared_ptr<ControllerData> data =
                std::make_shared<ControllerData>();

            // Listeners
            KeyboardListener::registerCallbacks(data);

            return data;
        }
};

#endif  // SOURCE_CONTROLLERS_CONTROLLER_H_
