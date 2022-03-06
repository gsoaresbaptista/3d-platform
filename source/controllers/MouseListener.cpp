#include "mouseListener.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include <memory>
#include <iostream>

//
vec2* MOUSE_DELTA;

void mouse_callback(int xpos, int ypos) {
    static bool first_mouse_pos = true;
    static float last_pos_x, last_pos_y = 0.0;

    if (first_mouse_pos) {
        MOUSE_DELTA->x = 0;
        MOUSE_DELTA->y = 0;
        last_pos_x = (float)xpos;
        last_pos_y = (float)ypos;
        first_mouse_pos = false;
    }

    MOUSE_DELTA->x = (float)xpos - last_pos_x;
    MOUSE_DELTA->y = (float)ypos - last_pos_y;
    last_pos_x = (float)xpos;
    last_pos_y = (float)ypos;


    if (xpos <= 100 || xpos >= 400 ||
        ypos <= 100 || ypos >= 400) {
        first_mouse_pos = true;
        glutWarpPointer(250, 250);
    }
}

void MouseListener::registerCallbacks(std::shared_ptr<ControllerData> data) {
    MOUSE_DELTA = &(data->mouse_delta);
    glutPassiveMotionFunc(mouse_callback);
}
