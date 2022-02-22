#include "./box.h"
#include "../../linear/vec3.h"
#include "../../style/color.h"
#include "../2d/rectangle.h"
#include <iostream>

Box::Box(vec3 center, GLfloat width, GLfloat height, GLfloat depth)
    : Shape(center) {
    this->width = width;
    this->height = height;
    this->depth = depth;
}
void Box::draw(std::shared_ptr<Texture> texture) {
    // Front
    vec3 p0(-width/2.0, height/2.0, depth/2.0);
    vec3 p1(-width/2.0, -height/2.0, depth/2.0);
    vec3 p2(width/2.0, -height/2.0, depth/2.0);
    vec3 p3(width/2.0, height/2.0, depth/2.0);

    // Back
    vec3 p4(width/2.0, height/2.0, -depth/2.0);
    vec3 p5(width/2.0, -height/2.0, -depth/2.0);
    vec3 p6(-width/2.0, -height/2.0, -depth/2.0);
    vec3 p7(-width/2.0, height/2.0, -depth/2.0);

    // Draw
    glNewList(this->id_, GL_COMPILE);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        if (texture != nullptr) texture->bind();
        Rectangle::draw(p0, p1, p2, p3, RED);  // Frente
        Rectangle::draw(p3, p2, p5, p4, BLUE);  // Direita
        Rectangle::draw(p4, p5, p6, p7, YELLOW);  // Trás
        Rectangle::draw(p7, p6, p1, p0, GREEN);  // Esquerda
        Rectangle::draw(p7, p0, p3, p4, ORANGE);  // Cima
        Rectangle::draw(p1, p6, p5, p2, VIOLET);  // Baixo
        if (texture != nullptr) texture->unbind();
    glEndList();
}
