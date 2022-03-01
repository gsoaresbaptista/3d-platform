#include "iostream"
#include "views/canvas.h"
#include "utils/shapes/3d/box.h"
#include "utils/shapes/shape.h"
#include "utils/shapes/3d/cylinder.h"
#include "utils/linear/vec3.h"
#include "utils/style/texture.h"
#include "utils/others/gameConstants.h"
#include <memory>
#include <GL/gl.h>
#include "utils/others/SVGReader.h"
#include "models/Arena.h"

#include "controllers/controller.h"
#include "controllers/keyboardListener.h"

int main() {
    Canvas canvas(800, 800, "Trabalho 3D");
    canvas.init();
    GameConstants::load_textures();
    // KeyboardListener::registerCallbacks();
    
    auto controllerData = Controller::registerCallbacks();

    auto data = readSVG("inputs/original_map.svg");
    auto arena = std::make_shared<Arena>(data, controllerData);
    arena->draw();

    canvas.subscription(arena);
    canvas.run();

    return 0;
}
