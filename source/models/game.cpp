#include "game.h"
#include "../utils/others/gameConstants.h"
#include <iostream>

Game::Game(
        std::shared_ptr<SVGData> data,
        std::shared_ptr<ControllerData> flags)
            : Shape(vec3(data->arena_width/2.0,
                data->arena_height/2.0,
                data->arena_depth/2.0)) {
    this->obstacles = data->rects;
    this->block_size = data->block_size;
    this->controller = flags;
}

void Game::draw(
        std::shared_ptr<Texture> texture,
        GLenum mode,
        Outline outline) {
    //
    for (auto& obstacle : obstacles) {
        obstacle->draw_block(block_size, GL_FILL);
    }
}

void Game::display() {
    // Move arena to origin
    glTranslatef(0, 0, -2*center.z);

    // TODO(all): Remove, temporary camera movement
    glTranslatef(
        controller->to_translate.x,
        controller->to_translate.y,
        controller->to_translate.z);

    glRotatef(controller->to_rotate.x, 1, 0, 0);
    glRotatef(controller->to_rotate.y, 0, 1, 0);
    glRotatef(controller->to_rotate.z, 0, 0, 1);

    // Draw arena obstacles
    for (auto& obstacle : obstacles) {
        glPushMatrix();
            obstacle->translate();
            glCallList(obstacle->getID());
        glPopMatrix();
    }
}