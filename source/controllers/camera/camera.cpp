#include "./camera.h"
#include <GL/glu.h>
#include <iostream>

Camera::Camera(vec3 pos) {
    this->position = vec3(pos);
    this->direction = vec3(0, 0, -1);
    this->left = vec3(-1, 0, 0);
    this->up = vec3(0, 1, 0);
    this->pitch = 0;
}

Camera::~Camera() {
}

void Camera::activate() {
    vec3 look = this->position + this->direction;
    gluLookAt(
        position.x, position.y, position.z,
        look.x, look.y, look.z,
        up.x, up.y, up.z);
}

void Camera::move_left() {
    vec3 velocity = this->left.normalize() * this->movement_constant;
    this->position = this->position + vec3(velocity.x, 0, velocity.z);
}

void Camera::move_right() {
    vec3 velocity = this->left.normalize() * (-this->movement_constant);
    this->position = this->position + vec3(velocity.x, velocity.y, velocity.z);
}

void Camera::move_forward() {
    vec3 velocity = this->direction * this->movement_constant;
    this->position = this->position + vec3(velocity.x, velocity.y, velocity.z);
}

void Camera::move_backward() {
    vec3 velocity = this->direction * (-this->movement_constant);
    this->position = this->position + vec3(velocity.x, velocity.y, velocity.z);
}

void Camera::increment_yaw(float dYaw) {
    this->yaw += dYaw;
}

void Camera::increment_pitch(float dPitch) {
    if (pitch + dPitch <= 45 && pitch + dPitch >= -45)
        this->pitch += dPitch;
}

void Camera::update() {
    float yaw = this->yaw * M_PI/180.0;
    float pitch = this->pitch * M_PI/180.0;
    this->direction = direction +
        vec3(-sin(yaw), sin(pitch), -cos(yaw)*cos(pitch));
    this->direction = direction.normalize();
    this->left = vec3(0, 1, 0) * this->direction;
    this->up = direction * left;
}
