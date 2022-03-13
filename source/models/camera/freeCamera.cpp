#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include "freeCamera.h"

FreeCamera::FreeCamera(
        CoordinateSystem* player, vec3 center,
        std::shared_ptr<SVGData> data,
        GLfloat block_size) : Camera(player) {
    //
    this->position = player->position;
    this->direction = player->direction;
    this->left = player->left;
    this->up = player->up;
    this->block_size = block_size;
    this->data = data;
    this->yaw = -90;
    this->pitch = 0;
    this->center = center;
}

void FreeCamera::increment_yaw(float dYaw) {
    this->yaw += dYaw;
}

void FreeCamera::increment_pitch(float dPitch) {
    if (pitch + dPitch <= 45 && pitch + dPitch >= -45)
        this->pitch += dPitch;
}

FreeCamera::~FreeCamera() {
}

void FreeCamera::activate() {
    glTranslatef(
        this->position.x,
        this->position.y,
        this->position.z);
}

void FreeCamera::update() {
    //
    this->position = (player->position + vec3(center.x - block_size, 0, 0))* -1.0;
    this->position.x += data->arena_height/2.f - block_size;
    this->position.y = 0;
    this->position.z = 0;

    //
    float width = (float)glutGet(GLUT_WINDOW_WIDTH);
    float height = (float)glutGet(GLUT_WINDOW_HEIGHT);
    float aspect = width/height;

    float diff = (800 - height) * (data->arena_height/2)/(800.0 / aspect) -
                 (800 - width) * (data->arena_height/2)/(800.0);

    // set the cameras if they go outside the map boundaries
    if (player->position.x + center.x - block_size - diff < data->arena_height/2.f - block_size) {
        // outside left boundary
        this->position.x = -diff;
    }

    if (player->position.x + center.x - block_size + data->arena_height/2.0 +
        block_size + diff > data->arena_width) {
        // outside right boundary
        this->position.x = -data->arena_width +
            data->arena_height + diff;
    }

    // Move camera off the map
    this->position.x -= data->arena_height/2.f;
    this->position.y -= data->arena_height/2.f;
    this->position.z -= 2*data->arena_depth + data->arena_height/1.5;

    //
    float yaw = this->yaw * M_PI/180.0;
    float pitch = this->pitch * M_PI/180.0;
    player->direction += vec3(-sin(yaw), sin(pitch), -cos(yaw)*cos(pitch));
    player->direction = player->direction.normalize();
    player->left = vec3(0, 1, 0) * player->direction;
    player->up = player->direction * player->left;
    player->yaw = this->yaw;
    player->pitch = this->pitch;
}
