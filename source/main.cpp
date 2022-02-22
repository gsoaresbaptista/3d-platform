#include "iostream"
#include "views/canvas.h"
#include "utils/shapes/3d/box.h"
#include "utils/linear/vec3.h"
#include "utils/style/texture.h"
#include <memory>

int main() {
    Canvas canvas(800, 800, "Trabalho 3D");
    canvas.init();

    auto texture = Texture::load("resources/textures/painted_brick.png", true);
    auto box = std::make_shared<Box>(vec3(0, 0, -5), 1, 1.3, 1);
    box->draw(texture);

    canvas.subscription(box);
    canvas.run();

    return 0;
}
