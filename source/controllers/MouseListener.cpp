#include "mouseListener.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include <memory>
#include <iostream>

//
static DefaultCamera* DEFAULT_CAMERA;
static OrbitalCamera* ORBITAL_CAMERA;
static GLboolean* MOVE_ORBITAL_CAMERA;
static float MOUSE_SENSITIVITY = 3;

vec2* MOUSE_DELTA;
static bool first_mouse_pos = true;
static float last_pos_x, last_pos_y = 0.0;

void mouse_callback(int xpos, int ypos) {
    if (first_mouse_pos) {
        MOUSE_DELTA->x = 0.0;
        MOUSE_DELTA->y = 0.0;
        last_pos_x = (float)xpos;
        last_pos_y = (float)ypos;
        first_mouse_pos = false;
    }

    MOUSE_DELTA->x = (float)xpos - last_pos_x;
    MOUSE_DELTA->y = (float)ypos - last_pos_y;
    last_pos_x = (float)xpos;
    last_pos_y = (float)ypos;

    //

    *MOUSE_DELTA = *MOUSE_DELTA * 0.01 * MOUSE_SENSITIVITY;

    if (DEFAULT_CAMERA != nullptr) {
        DEFAULT_CAMERA->increment_pitch(-MOUSE_DELTA->y);
        DEFAULT_CAMERA->increment_yaw(-MOUSE_DELTA->x);

    } else  if (ORBITAL_CAMERA != nullptr) {
        if (*MOVE_ORBITAL_CAMERA) {
            ORBITAL_CAMERA->increment_phi(-MOUSE_DELTA->y);
            ORBITAL_CAMERA->increment_theta(-MOUSE_DELTA->x);
        } else {
            ORBITAL_CAMERA->increment_phi(-MOUSE_DELTA->y);
            ORBITAL_CAMERA->increment_theta(-MOUSE_DELTA->x);
            ORBITAL_CAMERA->increment_pitch(-MOUSE_DELTA->y);
            ORBITAL_CAMERA->increment_yaw(-MOUSE_DELTA->x);
        }
    }

    if (xpos <= 100 || xpos >= 400 ||
        ypos <= 100 || ypos >= 400) {
        first_mouse_pos = true;
        glutWarpPointer(250, 250);
    }
}


void MouseListener::registerCallbacks(std::shared_ptr<ControllerData> data) {
    MOUSE_DELTA = &(data->mouse_delta);
    MOVE_ORBITAL_CAMERA = &(data->move_orbital_camera);
    glutPassiveMotionFunc(mouse_callback);
}

void MouseListener::set_camera(DefaultCamera* camera) {
    DEFAULT_CAMERA = camera;
    ORBITAL_CAMERA = nullptr;
}

void MouseListener::set_camera(OrbitalCamera* camera) {
    ORBITAL_CAMERA = camera;
    DEFAULT_CAMERA = nullptr;
}

void MouseListener::clear_camera() {
    DEFAULT_CAMERA = nullptr;
    ORBITAL_CAMERA = nullptr;
}

