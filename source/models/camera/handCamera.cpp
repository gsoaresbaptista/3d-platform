#include "handCamera.h"

void HandCamera::update() {


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

void HandCamera::set_player_angles() {
    this->direction = player->direction;
    this->left = player->left;
    this->up = player->up;
    this->yaw = player->yaw;
    this->pitch = player->pitch;
}


void HandCamera::activate() {
    vec3 position = player->position +
        vec3( center.x, 1.70*center.y, center.z) +
        vec3(block_size/4.f * cos((yaw+90) * M_PI/180.0) * cos(pitch * M_PI/180.0),
             - block_size/4.f * sin(pitch * M_PI/180.0),
            - block_size/4.f * sin((yaw+90) * M_PI/180.0));

    vec3 look = position + this->direction;

    gluLookAt(
        position.x, position.y, position.z,
        look.x, look.y, look.z,
        player->up.x, player->up.y, player->up.z);
}
