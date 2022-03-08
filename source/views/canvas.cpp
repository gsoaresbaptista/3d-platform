#include "canvas.h"
#include <GL/glut.h>
#include <GL/freeglut.h>

#include <iostream>

//
static GLuint canvas_width;
static GLuint canvas_height;
static GLuint canvas_id;
static GLuint canvas_fps;
static const char* canvas_name;

//
static GLdouble dt = 0;
static GLdouble currentTime = 0;
static GLdouble previousTime = 0;

//
static std::vector<std::shared_ptr<Shape>> canvas_shapes;

static void window_resize(float width, float height) {
    canvas_width = width;
    canvas_height = height;

    float aspect = (width > height) ? (width/height):(height/width);

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspect, 0.1, 500);
    glMatrixMode(GL_MODELVIEW);
}

Canvas::Canvas(GLuint width, GLuint height, const GLchar* name, GLuint fps) {
    canvas_width = width;
    canvas_height = height;
    canvas_name = name;
    canvas_fps = fps;
}

void Canvas::init() {
    int argc = 1;
    glutInit(&argc, NULL);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(canvas_width, canvas_height);
    canvas_id = glutCreateWindow(canvas_name);
    glutSetOption(
        GLUT_ACTION_ON_WINDOW_CLOSE,
        GLUT_ACTION_GLUTMAINLOOP_RETURNS);

    //
    glAlphaFunc(GL_GREATER, 0.5);
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_CW);
    glutSetCursor(GLUT_CURSOR_NONE);

    //
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_COLOR_MATERIAL);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

void Canvas::run() {
    glutTimerFunc(1000.0/canvas_fps, this->update, 0);
    glutMainLoop();
}

void Canvas::update(int value) {
    //
    glutTimerFunc(1000.0/canvas_fps, Canvas::update, 0);

    //
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    dt = (currentTime - previousTime)/1000;
    previousTime = currentTime;

    //
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    window_resize(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
    // glLoadIdentity();

    //
    glColor3f(1, 1, 1);
    for (auto& shape : canvas_shapes) {
        shape->display(dt);
    }

    //
    glutPostRedisplay();
    glutSwapBuffers();
}

void Canvas::subscription(std::shared_ptr<Shape> shape) {
    canvas_shapes.push_back(shape);
}
