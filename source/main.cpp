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
    auto box = std::make_shared<Box>(vec3(-1, 0, -5), 1, 1, 1);
    // box->draw(2, 2, nullptr, GL_LINE, Outline::ENTIRE);
    box->draw(2, 2, texture0, GL_FILL, Outline::ENTIRE);

    auto texture1 = Texture::load("resources/spruce_log.png", true);
    auto cylinder = std::make_shared<Cylinder>(vec3(0.5, 0, -5), 1, 0.5);
    cylinder->draw(30, 2, texture1, GL_FILL, Outline::SPLITTED);
    // cylinder->draw(30, 3, nullptr, GL_LINE, Outline::SPLITTED);

    canvas.subscription(box);
    canvas.subscription(cylinder);

    canvas.run();

    return 0;
}
