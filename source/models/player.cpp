#include "player.h"

Player::Player(vec3 center, GLfloat block_size) : Shape(center) {
    this->center = center;
    this->height = block_size;
    // printf("C: %f %f %f\n", this->center)
    this->collision_boundary = new Cylinder(
        this->center, 2*block_size, this->height);
}

void Player::draw(std::shared_ptr<Texture> texture,
    GLenum mode, Outline outline) {
    //
    this->collision_boundary->draw(30, 10, nullptr, GL_LINE, Outline::ENTIRE);
}

void Player::display(float dt) {
    glPushMatrix();
        this->translate();
        glPushMatrix();
            glRotatef(90, 1, 0, 0);
            glCallList(this->collision_boundary->getID());
        glPopMatrix();
    glPopMatrix();
}
