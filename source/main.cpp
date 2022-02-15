#include "iostream"
#include "views/canvas.h"
#include "utils/shapes/2d/rectangle.h"
#include "utils/shapes/2d/circle.h"
#include "utils/linear/vec2.h"
#include <memory>

int main() {
    Canvas canvas(800, 800, "Trabalho 3D");

    Shape* rect = new Rectangle(vec2(0, 0), 50, 40);
    Shape* circ = new Circle(vec2(0, 0), 20);

    canvas.subscription(rect);
    canvas.subscription(circ);

    canvas.init();
    canvas.run();

    return 0;
}
