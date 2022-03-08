#include "mouseListener.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include <memory>
#include <iostream>

//
static DefaultCamera* DEFAULT_CAMERA;
static OrbitalCamera* ORBITAL_CAMERA;
static GLboolean* MOVE_ORBITAL_CAMERA;
static float MOUSE_SENSITIVITY = 5;

vec2* MOUSE_DELTA;
static bool first_mouse_pos = true;
static float last_pos_x, last_pos_y = 0.0;

static int button_down = 0;

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
        }
    }

    if (xpos <= 300 || xpos >= 500 ||
        ypos <= 300 || ypos >= 500) {
        printf("%d, %d\n", xpos, ypos);
        first_mouse_pos = true;
        glutWarpPointer(400, 400);
    }
}

void mouse_callback(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        last_pos_x = x;
        last_pos_y = y;
        button_down = 1;
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        button_down = 0;
    }
}


void MouseListener::registerCallbacks(std::shared_ptr<ControllerData> data) {
    MOUSE_DELTA = &(data->mouse_delta);
    MOVE_ORBITAL_CAMERA = &(data->move_orbital_camera);
    glutPassiveMotionFunc(mouse_callback);
    glutMouseFunc(mouse_callback);
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

