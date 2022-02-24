#include "iostream"
#include "views/canvas.h"
#include "utils/shapes/3d/box.h"
#include "utils/shapes/shape.h"
#include "utils/shapes/3d/cylinder.h"
#include "utils/linear/vec3.h"
#include "utils/style/texture.h"
#include <memory>
#include <GL/gl.h>


int main() {
    Canvas canvas(800, 800, "Trabalho 3D");
    canvas.init();

    auto texture0 = Texture::load("resources/stone.png", true);
    auto box = std::make_shared<Box>(vec3(0, 0, -150), 100, 20, 10);
    box->draw(10, 2, nullptr, GL_LINE, Outline::ENTIRE);
    // box->draw(2, 2, texture0, GL_FILL, Outline::ENTIRE);

    canvas.subscription(box);

    canvas.run();

    return 0;
}
