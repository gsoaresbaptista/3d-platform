#include "circle.h"
#include <iostream>

Circle::Circle(vec3 center, GLfloat radius) : Shape(center) {
    this->radius = radius;
}

void Circle::draw(Texture* texture) {
    printf("Desenhando um círculo!\n");
}
