#include "Arena.h"
#include "../utils/others/gameConstants.h"
#include <iostream>

Arena::Arena(std::shared_ptr<SVGData> data, std::shared_ptr<ControllerData> cData) :
        Shape(vec3(
            data->arena_width/2.0,
            data->arena_height/2.0,
            data->arena_depth/2.0)
        ) {
    this->obstacles = data->rects;
    this->block_size = data->block_size;
    this->cData = cData;
}

void Arena::draw(
        std::shared_ptr<Texture> texture,
        GLenum mode,
        Outline outline) {
    //
    for (auto& obstacle : obstacles) {
        obstacle->draw_block(block_size, GL_FILL);
    }
}

void Arena::display() {
    glTranslatef(
        cData->to_translate.x,
        cData->to_translate.y,
        cData->to_translate.z);

    glTranslatef(0, 0, -2*center.z);

    glRotatef(cData->to_rotate.x, 1, 0, 0);
    glRotatef(cData->to_rotate.y, 0, 1, 0);
    glRotatef(cData->to_rotate.z, 0, 0, 1);


    for (auto& obstacle : obstacles) {
        glPushMatrix();
            obstacle->translate();
            glCallList(obstacle->getID());
        glPopMatrix();
    }
}
