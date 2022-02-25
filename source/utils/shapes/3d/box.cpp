#include "./box.h"
#include "../../linear/vec3.h"
#include "../../style/color.h"
#include "../2d/rectangle.h"

Box::Box(vec3 center, GLfloat width, GLfloat height, GLfloat depth)
    : Shape(center) {
    this->width = width;
    this->height = height;
    this->depth = depth;
}

void Box::draw(
        std::shared_ptr<Texture> texture,
        GLenum mode, Outline outline) {
    //
    draw(1, 1, texture, mode, outline);
}

void Box::draw(
        GLuint n_segs, GLuint n_stacks,
        std::shared_ptr<Texture> texture,
        GLenum mode, Outline outline, bool repeat_texture) {
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
        glPolygonMode(GL_FRONT, mode);
        if (texture != nullptr) texture->bind();
        Rectangle::draw(  // Frente
            p0, p1, p2, p3, n_segs, n_stacks, RED, outline, repeat_texture);
        Rectangle::draw(  // Direita
            p3, p2, p5, p4, n_segs, n_stacks, BLUE, outline, repeat_texture);
        Rectangle::draw(  // Trás
            p4, p5, p6, p7, n_segs, n_stacks, YELLOW, outline, repeat_texture);
        Rectangle::draw(  // Esquerda
            p7, p6, p1, p0, n_segs, n_stacks, GREEN, outline, repeat_texture);
        Rectangle::draw(  // Cima
            p7, p0, p3, p4, n_segs, n_stacks, ORANGE, outline, repeat_texture);
        Rectangle::draw(  // Baixo
            p1, p6, p5, p2, n_segs, n_stacks, VIOLET, outline, repeat_texture);
        if (texture != nullptr) texture->unbind();
    glEndList();
}
