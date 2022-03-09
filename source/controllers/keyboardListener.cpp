#include "keyboardListener.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include <memory>
#include <iostream>

//
static GLuint ANGLE_ID = -1;
static vec3* TRANSLATE_VECTOR;
static vec3* ANGLE_VECTOR;
static GLuint* KEYS;

static void key_down(unsigned char key, int x, int y) {
    switch (key) {
        case '1':
            KEYS['1'] = true;
            break;
        case '2':
            KEYS['2'] = true;
            break;
        case '3':
            KEYS['3'] = true;
            break;
        case '4':
            KEYS['4'] = true;
            break;
        case '5':
            KEYS['5'] = true;
            break;
        case 'd':
        case 'D':
            KEYS['d'] = true;
            break;
        case 'a':
        case 'A':
            KEYS['a'] = true;
            break;
        case 'w':
        case 'W':
            KEYS['w'] = true;
            break;
        case 's':
        case 'S':
            KEYS['s'] = true;
            break;
        case ' ':
            KEYS[' '] = true;
            break;
        case 'x':
        case 'X':
            KEYS['x'] = true;
            break;
        case '+':
            KEYS['+'] = true;
            break;
        case '-':
            KEYS['-'] = true;
            break;
        case 'm':
        case 'M':
            KEYS['m'] = true;
            break;
        case 'q':
        case 'Q':
            KEYS['q'] = true;
            break;
        case 27:  // ESC
            KEYS[27] = true;
            break;
    }
}

static void key_up(unsigned char key, int x, int y) {
    switch (key) {
        case '1':
            KEYS['1'] = false;
            break;
        case '2':
            KEYS['2'] = false;
            break;
        case '3':
            KEYS['3'] = false;
            break;
        case '4':
            KEYS['4'] = false;
            break;
        case '5':
            KEYS['5'] = false;
            break;
        case 'd':
        case 'D':
            KEYS['d'] = false;
            break;
        case 'a':
        case 'A':
            KEYS['a'] = false;
            break;
        case 'w':
        case 'W':
            KEYS['w'] = false;
            break;
        case 's':
        case 'S':
            KEYS['s'] = false;
            break;
        case ' ':
            KEYS[' '] = false;
            break;
        case 'x':
        case 'X':
            KEYS['x'] = false;
            break;
        case '+':
            KEYS['+'] = false;
            break;
        case '-':
            KEYS['-'] = false;
            break;
        case 'm':
        case 'M':
            KEYS['m'] = false;
            break;
        case 'q':
        case 'Q':
            KEYS['q'] = false;
            break;
        case 27:  // ESC
            KEYS[27] = false;
            break;
    }
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
    ANGLE_VECTOR = &(data->to_rotate);
    KEYS = data->keys;
    glutKeyboardFunc(key_down);
    glutKeyboardUpFunc(key_up);
    glutSpecialFunc(keyboard_special_function);
}
