#include <GL/glu.h>
#include <iostream>
#include "orbital.h"

Orbital::Orbital(float radius, float theta, float phi) {
    this->radius = radius;
    this->theta = theta;
    this->phi = phi;
    this->update();
}

Orbital::~Orbital() {
}

void Orbital::activate() {
    gluLookAt(
        position.x, position.y, position.z,
        look.x, look.y, look.z,
        0.f, 1.f, 0.f);
}

vec3 Orbital::cvt2cartesian() {
   float tmp_xy = this->radius*sin(phi*M_PI/180);
    float x = tmp_xy*sin(theta*M_PI/180);
    float y = this->radius*cos(phi*M_PI/180);
    float z = tmp_xy*cos(theta*M_PI/180);
    return vec3(x, y, z);
}

void Orbital::update() {
    this->position = cvt2cartesian();
    this->look = this->position * (-1);
}

void Orbital::forward() {
    vec3 dir = this->look.normalize();
    this->position = this->position + dir * (0.001);
    this->radius = position.magnitude();
}

void Orbital::backward() {
    vec3 dir = this->look.normalize();
    this->position = this->position + dir * (-0.001);
    this->radius = position.magnitude();
}

void Orbital::update_theta(float delta_theta) {
    this->theta = this->theta - delta_theta;
    this->update();
}

void Orbital::update_phi(float delta_phi) {
    this->phi = this->phi - delta_phi;
    if (this->phi < 30) this->phi = 30.f;
    if (this->phi > 150.f) this->phi = 150.f;
    this->update();
}
