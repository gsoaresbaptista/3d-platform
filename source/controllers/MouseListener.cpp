#include "mouseListener.h"
#include "../utils/libs/imgui/imgui.h"
#include "../utils/libs/imgui/imgui_impl_glut.h"
#include "../utils/libs/imgui/imgui_impl_opengl2.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include <memory>
#include <iostream>

//
static DefaultCamera* DEFAULT_CAMERA;
static OrbitalCamera* ORBITAL_CAMERA;
static FreeCamera* FREE_CAMERA;
static GLboolean* MOVE_ORBITAL_CAMERA;
static GLboolean* DISABLE_MOUSE;
static GLfloat* MOUSE_SENSITIVITY;
static GLboolean* BUTTON_DOWN;

vec2* MOUSE_DELTA;
static bool first_mouse_pos = true;
static float last_pos_x, last_pos_y = 0.0;

void mouse_callback(int xpos, int ypos) {
    if (!(*DISABLE_MOUSE)) {
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

        *MOUSE_DELTA = *MOUSE_DELTA * 0.01 * (*MOUSE_SENSITIVITY);

        if (DEFAULT_CAMERA != nullptr) {
            DEFAULT_CAMERA->increment_pitch(-MOUSE_DELTA->y);
            DEFAULT_CAMERA->increment_yaw(-MOUSE_DELTA->x);

        } else  if (ORBITAL_CAMERA != nullptr) {
            if (*MOVE_ORBITAL_CAMERA) {
                ORBITAL_CAMERA->increment_phi(-MOUSE_DELTA->y, false);
                ORBITAL_CAMERA->increment_theta(-MOUSE_DELTA->x, false);
            } else {
                ORBITAL_CAMERA->increment_pitch(-MOUSE_DELTA->y, true);
                ORBITAL_CAMERA->increment_yaw(-MOUSE_DELTA->x, true);
            }
        } else  if (FREE_CAMERA != nullptr) {
            FREE_CAMERA->increment_pitch(-MOUSE_DELTA->y);
            FREE_CAMERA->increment_yaw(-MOUSE_DELTA->x);
        }

        //
        if (xpos <= 100 || xpos >= 400 ||
            ypos <= 100 || ypos >= 400) {
            first_mouse_pos = true;
            glutWarpPointer(250, 250);
        }
    }
}

void mouse_callback(int button, int state, int x, int y) {
    ImGui_ImplGLUT_MouseFunc(button, state, x, y);
    ImGui_ImplGLUT_MotionFunc(x, y);

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        last_pos_x = x;
        last_pos_y = y;
        *BUTTON_DOWN = true;
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        *BUTTON_DOWN = false;
    }

    glutPostRedisplay();
}

void MouseListener::registerCallbacks(std::shared_ptr<ControllerData> data) {
    BUTTON_DOWN = &(data->mouse_button);
    MOUSE_DELTA = &(data->mouse_delta);
    MOVE_ORBITAL_CAMERA = &(data->move_orbital_camera);
    DISABLE_MOUSE = &(data->disable_mouse_warp);
    MOUSE_SENSITIVITY = &(data->mouse_sensitivity);
    glutPassiveMotionFunc(mouse_callback);
    glutMotionFunc(mouse_callback);
    glutMouseFunc(mouse_callback);
}

void MouseListener::set_camera(DefaultCamera* camera) {
    DEFAULT_CAMERA = camera;
    ORBITAL_CAMERA = nullptr;
    FREE_CAMERA = nullptr;
}

void MouseListener::set_camera(OrbitalCamera* camera) {
    ORBITAL_CAMERA = camera;
    DEFAULT_CAMERA = nullptr;
    FREE_CAMERA = nullptr;
}

void MouseListener::set_camera(FreeCamera* camera) {
    ORBITAL_CAMERA = nullptr;
    DEFAULT_CAMERA = nullptr;
    FREE_CAMERA = camera;
}

void MouseListener::clear_camera() {
    DEFAULT_CAMERA = nullptr;
    ORBITAL_CAMERA = nullptr;
}

