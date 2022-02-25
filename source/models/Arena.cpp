#include "Arena.h"
#include <iostream>

Arena::Arena(std::shared_ptr<SVGReader> data) :
        Shape(vec3(
            data->arena_width/2.0,
            data->arena_height/2.0,
            data->arena_depth/2.0)
        ) {
    this->obstacles = data->rects;
}

void Arena::draw(
        std::shared_ptr<Texture> texture,
        GLenum mode,
        Outline outline) {
    //
    for (auto& obstacle : obstacles) {
        obstacle->draw(nullptr, GL_FILL, Outline::ENTIRE);
    }
}

void Arena::display() {
    glTranslatef(0, -4*center.y, -20*abs(center.z));

    for (auto& obstacle : obstacles) {
        glPushMatrix();
            obstacle->translate();
            glCallList(obstacle->getID());
        glPopMatrix();
    }
}
