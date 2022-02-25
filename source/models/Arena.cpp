#include "Arena.h"
#include <iostream>

Arena::Arena(SVGReader* data) :
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

float angle = 0;

void Arena::display() {
    glTranslatef(0, -center.y, 0);
    glTranslatef(0, 0, -500 - center.z);
    glRotatef(angle, 0, 1, 0);
    // glRotatef(angle, 0, 0, 1);

    // glCallList(obstacles[0]->getID());
    // glCallList(obstacles[1]->getID());
    // glCallList(obstacles[02]->getID());

    for (auto& obstacle : obstacles) {
        // std::cout << "QUADRADO!" << std::endl;
        glPushMatrix();
            obstacle->translate();
            glCallList(obstacle->getID());
        glPopMatrix();
    }

    angle += 0.6;
    angle = (angle >= 360) ? 0:angle;
}
