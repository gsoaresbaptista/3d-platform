#include "player.h"
#include "../utils/shapes/2d/rectangle.h"
#include "../utils/style/steve.h"

Player::Player(vec3 center, GLfloat block_size) : Shape(center) {
    this->center = center;
    this->height = block_size;
    this->collision_boundary = new Cylinder(
        this->center, 2*block_size, block_size/2.f);

    //
    this->center.y = block_size;

    //
    this->coordinateSystem = new CoordinateSystem();
    this->coordinateSystem->direction = vec3(1, 0, 0);
    this->coordinateSystem->left = vec3(0, 0, -1);
    this->coordinateSystem->up = vec3(0, 1, 0);

    //
    this->falling = false;
    this->rising = false;
    this->on_air_time = 0;

    //
    this->dheight = height/2.25f;
    head = glGenLists(6);
    body = head + 1;
    arm0 = head + 2, arm1 = head + 3;
    leg0 = head + 4, leg1 = head + 5;
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

void Player::set_coordinate_system(CoordinateSystem* system) {
    this->coordinateSystem->direction = system->direction;
    this->coordinateSystem->left = system->left;
    this->coordinateSystem->up = system->up;
    this->coordinateSystem->position = system->position;
}

GLfloat Player::get_width() {
    return this->height;
}

GLfloat Player::get_height() {
    return this->height*2;
}

GLfloat Player::get_depth() {
    return this->height;
}


void Player::draw(std::shared_ptr<Texture> texture,
    GLenum mode, Outline outline) {
    //
    steve::draw_head(head, dheight);
    steve::draw_body(body, dheight);
    steve::draw_arm(arm0, arm1, dheight);
    steve::draw_leg(leg0, leg1, dheight);
    this->collision_boundary->draw(30, 10, nullptr, GL_LINE, Outline::ENTIRE);
}

void Player::display_character() {
    glPushMatrix();
        glTranslatef(0, -dheight *1.25, 0);
        glPushMatrix();
            glTranslatef(0, 3*dheight, 0);
            glCallList(head);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-dheight*0.75, 2*dheight, 0);
            glCallList(arm0);
            glTranslatef(0, -dheight, 0);
            glCallList(arm1);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(dheight*0.75, 2*dheight, 0);
            glCallList(arm0);
            glTranslatef(0, -dheight, 0);
            glCallList(arm1);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0, 2*dheight, 0);
            glCallList(body);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(dheight/4.f, -dheight/2.f, 0);
            glCallList(leg1);
            glTranslatef(0, dheight, 0);
            glCallList(leg0);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-dheight/4.f, -dheight/2.f, 0);
            glCallList(leg1);
            glTranslatef(0, dheight, 0);
            glCallList(leg0);
        glPopMatrix();
    glPopMatrix();
}

void Player::set_x(GLfloat x) {
    this->coordinateSystem->position.x = x;
}

void Player::set_y(GLfloat y) {
    this->coordinateSystem->position.y = y;
}

void Player::set_z(GLfloat z) {
    this->coordinateSystem->position.z = z;
}

void Player::move_left_right(vec3 direction) {
    vec3 velocity = direction;
    coordinateSystem->position += vec3(velocity.x, 0, velocity.z);
}

void Player::move_forward_backward(vec3 direction) {
    vec3 velocity = direction;
    coordinateSystem->position += vec3(velocity.x, 0, velocity.z);
}

void Player::move_up(GLfloat direction) {
    vec3 velocity = coordinateSystem->up.normalize() * direction;
    coordinateSystem->position += vec3(0, velocity.y, 0);
}

CoordinateSystem* Player::get_coordinate_system() {
    return this->coordinateSystem;
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
    return coordinateSystem->position.y + center.y - height;
}

void Player::set_rising(GLboolean flag) {
    this->rising = flag;
}

GLfloat Player::get_on_air_time() {
    return this->on_air_time;
}

void Player::display(float dt) {
    float d = height/2.f;

    glPushMatrix();
        this->translate();
        glTranslatef(
            coordinateSystem->position.x,
            coordinateSystem->position.y,
            coordinateSystem->position.z);
        //

        glPushMatrix();
            glRotatef(90, 1, 0, 0);
            this->collision_boundary->display(dt);
        glPopMatrix();

        glColor3f(1, 1, 1);
        this->display_character();

    glPopMatrix();
}

vec3 Player::get_position() {
    return this->coordinateSystem->position;
}

GLfloat Player::get_collision_radius() {
    return this->collision_boundary->get_radius();
}

GLfloat Player::get_head_height() {
    return coordinateSystem->position.y + center.y;
}