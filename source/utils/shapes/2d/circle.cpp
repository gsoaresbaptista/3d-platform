#include "circle.h"
#include <iostream>

Circle::Circle(vec2 center, GLfloat radius) : Shape(center) {
    this->radius = radius;
}

void Circle::draw(Color color) {
    printf("Desenhando um círculo!\n");
}
