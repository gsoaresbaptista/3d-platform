#include "player.h"
#include "../utils/shapes/2d/rectangle.h"
#include "../utils/style/steve.h"
#include "../utils/others/angles/steve/arm_bow.h"
#include "../utils/others/angles/steve/leg.h"

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

    for (int i = 0; i < 8; i++) {
        this->angles[i] = arm_bow[0][i];
    }

    for (int i = 8; i < 21; i++) {
        this->angles[i] = leg_angles[0][i];
    }

    //
    this->show_collision_boundary = false;

    //
    this->walking = false;
    this->accumulated_time_bow_animation = 0;
    this->accumulated_time_leg_animation = 0;
    this->bow_animation_angle_id = 0;
    this->bow_state_id = 0;
}

Player::~Player() {
    delete this->collision_boundary;
}

void Player::increment_on_air_time(GLfloat dt) {
    this->on_air_time += dt;
}

void Player::clear_on_air_time() {
    this->on_air_time = 0;

    for (int i = 8; i < 21; i++) {
        this->angles[i] = leg_angles[0][i];
    }
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

void Player::increment_bow_animation(float dt) {
    if (dt < 0) {
        bow_animation_angle_id = 0;
        accumulated_time_bow_animation = 0;

        //
        for (int i = 0; i < 8; i++)
            this->angles[i] = arm_bow[bow_animation_angle_id][i];
        bow_state_id = arm_bow[bow_animation_angle_id][21];

    } else if (bow_animation_angle_id != 49) {
        this->accumulated_time_bow_animation += dt;

        //
        if (accumulated_time_bow_animation >= 1.f/1000.f) {
            this->accumulated_time_bow_animation = 0;
            this->bow_animation_angle_id++;

            if (bow_animation_angle_id > 49)
            this->bow_animation_angle_id = 0;

            for (int i = 0; i < 8; i++)
                this->angles[i] = arm_bow[bow_animation_angle_id][i];
            bow_state_id = arm_bow[bow_animation_angle_id][21];
        }
    }
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
        glRotatef(180, 0, 1, 0);

        glPushMatrix();
            glTranslatef(0, 3*dheight, 0);
            glTranslatef(0, -dheight/2.f, 0);
            glRotatef(this->coordinateSystem->pitch, -1, 0, 0);
            glTranslatef(0, dheight/2.f, 0);
            glCallList(head);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(dheight*0.75, 2*dheight, 0);
            glTranslatef(dheight/4.f, dheight/2.f, 0.0);
            glRotatef(angles[0], 1, 0, 0);
            glRotatef(angles[1], 0, 0, 1);
            glTranslatef(-dheight/4.f, -dheight/2.f, 0.0);
            glRotatef(coordinateSystem->pitch, -1, 0, 0);
            glCallList(arm0);
            glTranslatef(0, -dheight, 0);
            glTranslatef(dheight/4.f, dheight/2.f, -dheight/4.f);
            glRotatef(-angles[2], 1, 0, 0);
            glRotatef(-angles[3], 0, 0, 1);
            glTranslatef(-dheight/4.f, -dheight/2.f, dheight/4.f);
            glCallList(arm1);
            glTranslatef(-dheight/4.f, dheight/2.f, 0);
            glRotatef(-90, 0, 0, 1);
            glRotatef(90, 1, 0, 0);
            glCallList(BOW_MODEL[bow_state_id]);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-dheight*0.75, 2*dheight, 0);
            glTranslatef(dheight/4.f, dheight/2.f, 0.0);
            glRotatef(angles[4], 1, 0, 0);
            glRotatef(angles[5], 0, 0, 1);
            glTranslatef(-dheight/4.f, -dheight/2.f, 0.0);
            glRotatef(coordinateSystem->pitch, -1, 0, 0);
            glCallList(arm0);
            glTranslatef(0, -dheight, 0);
            glTranslatef(dheight/15.5f, dheight/2.f, -1.5*dheight);
            glRotatef(angles[6], 1, 0, 0);
            glRotatef(angles[7], 0, 0, 1);
            glTranslatef(-dheight/15.5f, -dheight/2.f, 1.5*dheight);
            glCallList(arm1);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0, 2*dheight, 0);
            glCallList(body);
        glPopMatrix();

        glPushMatrix();
            //
            glTranslatef(dheight/4.f, dheight/2.f, 0);
            glTranslatef(0, dheight/2.f, 0);
            glRotatef(angles[8], 1, 0, 0);
            glRotatef(angles[9], 0, 0, 1);
            glTranslatef(0, -dheight/2.f, 0);
            glCallList(leg0);

            glTranslatef(0, -dheight, 0);
            glTranslatef(0, dheight/2.f, 0);
            glRotatef(angles[14], 1, 0, 0);
            glRotatef(angles[15], 0, 0, 1);
            glTranslatef(0, -dheight/2.f, 0);
            glCallList(leg1);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-dheight/4.f, dheight/2.f, 0);
            glTranslatef(0, dheight/2.f, 0);
            glRotatef(angles[12], 1, 0, 0);
            glRotatef(angles[13], 0, 0, 1);
            glTranslatef(0, -dheight/2.f, 0);
            glCallList(leg0);

            glTranslatef(0, -dheight, 0);
            glTranslatef(0, dheight/2.f, 0);
            glRotatef(angles[14], 1, 0, 0);
            glRotatef(angles[15], 0, 0, 1);
            glTranslatef(0, -dheight/2.f, 0);
            glCallList(leg1);
        glPopMatrix();
    glPopMatrix();
}

vec3 Player::get_hand_position() {
}

void Player::set_x(GLfloat x) {
    this->coordinateSystem->position.x = x;
}

void Player::set_y(GLfloat y) {
    this->coordinateSystem->position.y = y;
}

bool Player::ready2shoot() {
    return this->bow_state_id == 49;
}

void Player::set_z(GLfloat z) {
    this->coordinateSystem->position.z = z;
}

void Player::move_left_right(vec3 direction) {
    this->walking = true;
    vec3 velocity = direction;
    coordinateSystem->position += vec3(velocity.x, 0, velocity.z);
}

void Player::move_forward_backward(vec3 direction) {
    this->walking = true;
    vec3 velocity = direction;
    coordinateSystem->position += vec3(velocity.x, 0, velocity.z);
}

void Player::clear_walking() {
    this->walking = false;
    this->accumulated_time_leg_animation = 0;
    this->leg_animation_angle_id = 0;
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


    if (walking) {
        this->accumulated_time_leg_animation += dt;

        if (accumulated_time_leg_animation >= 0.5/1000.f) {
            this->accumulated_time_leg_animation = 0;
            this->leg_animation_angle_id++;

            if (leg_animation_angle_id > 35)
                this->leg_animation_angle_id = 0;

            for (int i = 8; i < 21; i++)
                this->angles[i] = leg_angles[leg_animation_angle_id][i];
        }
    }

    glPushMatrix();
        this->translate();
        glTranslatef(
            coordinateSystem->position.x,
            coordinateSystem->position.y,
            coordinateSystem->position.z);
        //
        if (this->show_collision_boundary) {
            glPushMatrix();
                glRotatef(90, 1, 0, 0);
                this->collision_boundary->display(dt);
            glPopMatrix();
        }

        glRotatef(coordinateSystem->yaw, 0, 1, 0);
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

void Player::set_show_collision_boundary(GLboolean value) {
    this->show_collision_boundary = value;
}
