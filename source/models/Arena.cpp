#include "Arena.h"
#include <iostream>

Arena::Arena(std::shared_ptr<SVGReader> data) :
        Shape(vec3(
            data->arena_width/2.0,
            data->arena_height/2.0,
            data->arena_depth/2.0)
        ) {
    this->obstacles = data->rects;
    this->block_size = data->block_size;
    this->stone = Texture::load("resources/oak_planks.png", true);
}

void Arena::draw(
        std::shared_ptr<Texture> texture,
        GLenum mode,
        Outline outline) {
    //
    for (auto& obstacle : obstacles) {
        obstacle->draw_block(block_size, stone, GL_FILL);
    }
}

void Arena::display() {
    glTranslatef(0, 0, -2*center.z);

    for (auto& obstacle : obstacles) {
        glPushMatrix();
            obstacle->translate();
            glCallList(obstacle->getID());
        glPopMatrix();
    }
}
