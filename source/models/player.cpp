#include "player.h"

Player::Player(vec3 center, GLfloat block_size) : Shape(center) {
    this->center = center;
    this->height = block_size;
    this->collision_boundary = new Cylinder(
        this->center, 2*block_size, this->height);

    //
    this->direction = vec3(1, 0, 0);
    this->left = vec3(0, 0, -1);
    this->up = vec3(0, 1, 0);

    //
    this->falling = false;
    this->rising = false;
    this->on_air_time = 0;
}

Player::~Player() {
    delete this->collision_boundary;
}

void Player::increment_on_air_time(GLfloat dt) {
    this->on_air_time += dt;
}

void Player::clear_on_air_time() {
    this->on_air_time = 0;
}

void Player::draw(std::shared_ptr<Texture> texture,
    GLenum mode, Outline outline) {
    //
    this->collision_boundary->draw(30, 10, nullptr, GL_LINE, Outline::ENTIRE);
}

void Player::set_y(GLfloat y) {
    this->position.y = y;
}

void Player::move_left_right(GLfloat direction) {
    vec3 velocity = left.normalize() * direction;
    this->position = this->position + vec3(velocity.x, 0, velocity.z);
}

void Player::move_forward_backward(GLfloat direction) {
    vec3 velocity = this->direction.normalize() * direction;
    this->position = this->position + vec3(velocity.x, 0, velocity.z);
}

void Player::move_up(GLfloat direction) {
    vec3 velocity = this->up.normalize() * direction;
    this->position = this->position + vec3(0, velocity.y, 0);
}

vec3 Player::get_position() {
    return this->position;
}

GLboolean Player::is_falling() {
    return this->falling;
}

void Player::set_falling(GLboolean flag) {
    this->falling = flag;
}

GLboolean Player::is_rising() {
    return this->rising;
}

GLfloat Player::get_feet_height() {
    return position.y + center.y - height;
}

void Player::set_rising(GLboolean flag) {
    this->rising = flag;
}

GLfloat Player::get_on_air_time() {
    return this->on_air_time;
}

void Player::display(float dt) {
    glPushMatrix();
        this->translate();
        glTranslatef(position.x, position.y, position.z);
        glPushMatrix();
            glRotatef(90, 1, 0, 0);
            glCallList(this->collision_boundary->getID());
        glPopMatrix();
    glPopMatrix();
}
