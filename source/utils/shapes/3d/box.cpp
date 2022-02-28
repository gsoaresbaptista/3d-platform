#include "./box.h"
#include "../../linear/vec3.h"
#include "../../style/color.h"
#include "../../style/gameTexture.h"
#include "../2d/rectangle.h"

Box::Box(
    vec3 center, GLfloat width, GLfloat height,
    GLfloat depth, BoxType type) : Shape(center) {
    this->width = width;
    this->height = height;
    this->depth = depth;
    this->type = type;
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
        GLenum mode, Outline outline) {
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
            p0, p1, p2, p3, n_segs, n_stacks, RED, outline);
        Rectangle::draw(  // Direita
            p3, p2, p5, p4, n_segs, n_stacks, BLUE, outline);
        Rectangle::draw(  // Trás
            p4, p5, p6, p7, n_segs, n_stacks, YELLOW, outline);
        Rectangle::draw(  // Esquerda
            p7, p6, p1, p0, n_segs, n_stacks, GREEN, outline);
        Rectangle::draw(  // Cima
            p7, p0, p3, p4, n_segs, n_stacks, ORANGE, outline);
        Rectangle::draw(  // Baixo
            p1, p6, p5, p2, n_segs, n_stacks, VIOLET, outline);
        if (texture != nullptr) texture->unbind();
    glEndList();
}

void Box::draw_block(GLfloat block_size, GLenum mode) {
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

    std::shared_ptr<Texture> block_tex;

    if (this->type == BoxType::STONE)
        // block_tex = STONE_TEX;
        block_tex = BRICKS_TEX;
    else
        block_tex = SPRUCE_PLANKS_TEX;

    // Draw
    glNewList(this->id_, GL_COMPILE);
        glPolygonMode(GL_FRONT, mode);
        block_tex->bind();
        Rectangle::draw_block(  // Frente
            p0, p1, p2, p3, block_size, RED);
        Rectangle::draw_block(  // Direita
            p3, p2, p5, p4, block_size, BLUE);
        Rectangle::draw_block(  // Trás
            p4, p5, p6, p7, block_size, YELLOW);
        Rectangle::draw_block(  // Esquerda
            p7, p6, p1, p0, block_size, GREEN);
        Rectangle::draw_block(  // Cima
            p7, p0, p3, p4, block_size, ORANGE);
        Rectangle::draw_block(  // Baixo
            p1, p6, p5, p2, block_size, VIOLET);
        block_tex->unbind();
    glEndList();
}

GLfloat Box::get_width() {
    return this->width;
}

GLfloat Box::get_height() {
    return this->height;
}

GLfloat Box::get_depth() {
    return this->depth;
}
