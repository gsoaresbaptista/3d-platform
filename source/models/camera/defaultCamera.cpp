#include <GL/glu.h>
#include <iostream>
#include "defaultCamera.h"

DefaultCamera::DefaultCamera(
        CoordinateSystem* player, vec3 center) : Camera(player) {
    this->center = center;
    this->pitch = 0;
    this->yaw = -90 * player->direction.x;
    this->direction = player->direction;
    this->up = player->up;
    this->left = player->left;
}

DefaultCamera::~DefaultCamera() {
}

void DefaultCamera::increment_yaw(float dYaw) {
    this->yaw += dYaw;
}

void DefaultCamera::increment_pitch(float dPitch) {
    if (pitch + dPitch <= 45 && pitch + dPitch >= -45)
        this->pitch += dPitch;
}

float DefaultCamera::get_yaw() {
    return this->yaw;
}

float DefaultCamera::get_pitch() {
    return this->pitch;
}


void DefaultCamera::update() {
    float yaw = this->yaw * M_PI/180.0;
    float pitch = this->pitch * M_PI/180.0;
    this->direction += vec3(-sin(yaw), sin(pitch), -cos(yaw)*cos(pitch));
    this->direction = this->direction.normalize();
    this->left = vec3(0, 1, 0) * this->direction;
    this->up = this->direction * this->left;
    player->yaw = this->yaw;
    player->pitch = this->pitch;

    //
    this->player->direction = direction;
    this->player->left = left;
    this->player->up = up;
}

void DefaultCamera::set_player_angles() {
    this->direction = player->direction;
    this->left = player->left;
    this->up = player->up;
    this->yaw = player->yaw;
    this->pitch = player->pitch;
}

void DefaultCamera::activate() {
    vec3 position = player->position +
        vec3(center.x, 1.65*center.y, center.z);

    vec3 look = position + this->direction;

    gluLookAt(
        position.x, position.y, position.z,
        look.x, look.y, look.z,
        player->up.x, player->up.y, player->up.z);
}

