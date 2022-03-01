#include "keyboardListener.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include <memory>
#include <iostream>

//
static GLuint ANGLE_ID = -1;
static vec3* TRANSLATE_VECTOR;
static vec3*ANGLE_VECTOR;

static void keyboard_function(unsigned char key, int x, int y) {
}

static void keyboard_special_function(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            if (ANGLE_ID == -1) {
                TRANSLATE_VECTOR->y -= 1.0;
            } else {
                if (ANGLE_ID == 0) ANGLE_VECTOR->x -= 1.0;
                if (ANGLE_ID == 1) ANGLE_VECTOR->y -= 1.0;
                if (ANGLE_ID == 2) ANGLE_VECTOR->z -= 1.0;
            }
            break;
        case GLUT_KEY_DOWN:
            if (ANGLE_ID == -1) {
                TRANSLATE_VECTOR->y += 1.0;
            } else {
                if (ANGLE_ID == 0) ANGLE_VECTOR->x += 1.0;
                if (ANGLE_ID == 1) ANGLE_VECTOR->y += 1.0;
                if (ANGLE_ID == 2) ANGLE_VECTOR->z += 1.0;
            }
            break;
        case GLUT_KEY_LEFT:
            if (ANGLE_ID == -1) TRANSLATE_VECTOR->x += 1.0;
            break;
        case GLUT_KEY_RIGHT:
            if (ANGLE_ID == -1) TRANSLATE_VECTOR->x -= 1.0;
            break;
        case GLUT_KEY_F1:
            ANGLE_ID = -1;
            break;
        case GLUT_KEY_F2:
            ANGLE_ID = 0;
            break;
        case GLUT_KEY_F3:
            ANGLE_ID = 1;
            break;
        case GLUT_KEY_F4:
            ANGLE_ID = 2;
            break;
    }
}

void KeyboardListener::registerCallbacks(std::shared_ptr<ControllerData> data) {
    TRANSLATE_VECTOR = &(data->to_translate);
    ANGLE_VECTOR = &(data->to_rotate);
    glutKeyboardFunc(keyboard_function);
    glutSpecialFunc(keyboard_special_function);
}
