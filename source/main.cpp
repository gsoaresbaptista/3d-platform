#include "iostream"
#include "views/canvas.h"
#include "utils/shapes/3d/box.h"
#include "utils/shapes/shape.h"
#include "utils/shapes/3d/cylinder.h"
#include "utils/math/math.h"
#include "utils/style/texture.h"
#include "utils/others/gameConstants.h"
#include <memory>
#include <GL/gl.h>
#include "utils/others/SVGReader.h"
#include "models/game.h"

#include "controllers/controller.h"
#include "controllers/keyboardListener.h"

int main() {
    Canvas canvas(800, 800, "Trabalho 3D");
    canvas.init();
    GameConstants::load_textures();
    GameConstants::load_materials();
    GameConstants::load_models();
    auto controllerData = Controller::registerCallbacks();

    auto data = readSVG("inputs/test.svg");
    auto game = std::make_shared<Game>(data, controllerData);
    game->draw();

    canvas.subscription(game);
    canvas.run();

    return 0;
}
