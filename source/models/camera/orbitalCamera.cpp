#include <GL/glu.h>
#include <iostream>
#include "orbitalCamera.h"

OrbitalCamera::OrbitalCamera(
        CoordinateSystem* player,
        vec3 center,
        float block_size) : Camera(player) {
    this->block_size = block_size;
    this->radius = block_size*8;
    this->theta = -90.f;
    this->phi = 60.f;
    this->center = center;
    this->pitch = 0;
    this->yaw = -90;
    this->update();
}

OrbitalCamera::~OrbitalCamera() {
}

void OrbitalCamera::activate() {
    gluLookAt(
        position.x, position.y, position.z,
        look.x, look.y, look.z,
        player->up.x, player->up.y, player->up.z);
}

vec3 OrbitalCamera::cvt2cartesian() {
    float tmp_xy = this->radius*sin(phi*M_PI/180);
    float x = tmp_xy*sin(theta*M_PI/180);
    float y = this->radius*cos(phi*M_PI/180);
    float z = tmp_xy*cos(theta*M_PI/180);
    return vec3(x, y, z);
}

void OrbitalCamera::update() {
    this->position = cvt2cartesian() + player->position + center;
    this->look = cvt2cartesian() * (-1) + player->position + center;
}

void OrbitalCamera::zoom_in() {
    this->radius -= block_size/3;
}

void OrbitalCamera::zoom_out() {
    this->radius += block_size/3;
}

void OrbitalCamera::increment_theta(float delta_theta) {
    this->theta = this->theta - delta_theta;
    this->update();
}

void OrbitalCamera::increment_phi(float delta_phi) {
    this->phi = this->phi - delta_phi;
    if (this->phi < 30) this->phi = 30.f;
    if (this->phi > 150.f) this->phi = 150.f;
    this->update();
}
