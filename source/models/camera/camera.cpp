#include <GL/glu.h>
#include <iostream>
#include "camera.h"

Camera::Camera(CoordinateSystem* player) {
    this->player = player;
}

Camera::~Camera() {
}
