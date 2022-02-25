#include "iostream"
#include "views/canvas.h"
#include "utils/shapes/3d/box.h"
#include "utils/shapes/shape.h"
#include "utils/shapes/3d/cylinder.h"
#include "utils/linear/vec3.h"
#include "utils/style/texture.h"
#include <memory>
#include <GL/gl.h>
#include "utils/others/SVGReader.h"
#include "models/Arena.h"

int main() {
    Canvas canvas(800, 800, "Trabalho 3D");
    canvas.init();

    SVGReader* data = readSVG("inputs/original_map.svg");
    auto arena = std::make_shared<Arena>(data);
    arena->draw();

    // auto texture0 = Texture::load("resources/stone.png", true);
    // auto box0 = std::make_shared<Box>(vec3(-26, 0, -150), 50, 20, 10);
    // auto box1 = std::make_shared<Box>(vec3(+26, 0, -150), 50, 20, 10);
    // box0->draw(10, 2, texture0, GL_FILL, Outline::ENTIRE, true);
    // box1->draw(10, 2, texture0, GL_FILL, Outline::ENTIRE, false);

    // canvas.subscription(box0);
    // canvas.subscription(box1);
    canvas.subscription(arena);
    canvas.run();

    return 0;
}
