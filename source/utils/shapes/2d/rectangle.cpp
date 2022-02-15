#include "rectangle.h"
#include <iostream>

Rectangle::Rectangle(vec2 center, GLfloat width, GLfloat height)
         : Shape(center) {
    this->width = width;
    this->height = height;
}

void Rectangle::draw(Color color) {
    printf("Desenhando um retângulo!\n");
}
