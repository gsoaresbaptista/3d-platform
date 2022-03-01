#include "canvas.h"
#include <GL/glut.h>
#include <iostream>

// TODO(all): Remove
#include "../utils/shapes/3d/cylinder.h"

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

float angle = 0;
float lado = 1;


static void draw_coords_system() {
    glTranslatef(0, 0, -100);
    // glRotatef(angle, 1, 0, 0);
    // glRotatef(angle, 0, 1, 0);
    // glRotatef(angle, 0, 0, 1);
    // glRotatef(-270, 0, 1, 0);

    // auto cylinder = std::make_shared<Cylinder>(vec3(0, 0, 0), 10000, 0.5);

    // cylinder->draw(nullptr, GL_FILL, Outline::ENTIRE);
    // glPushMatrix();
    //     cylinder->translate();
    //     glTranslatef(0, 0, -10000/2);
    //     cylinder->display();
    // glPopMatrix();

    // glPushMatrix();
    //     glRotatef(-90, 1, 0, 0);
    //     glTranslatef(0, 0, 10000/2.0002);
    //     cylinder->display();
    // glPopMatrix();

    // glPushMatrix();
    //     glRotatef(90, 0, 1, 0);
    //     glTranslatef(0, 0, 10000/2);
    //     cylinder->display();
    // glPopMatrix();

    // if (abs(angle) >= 45 || abs(angle) >= 90) lado *= -1;
    // angle += 0.6 * lado;
    angle = (angle >= 360)? 0: angle+0.6;
}

static void window_resize(float width, float height) {
    canvas_width = width;
    canvas_height = height;

    float aspect = (width > height) ? (width/height):(height/width);

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspect, 0.1, 1000);
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

    //
    glAlphaFunc(GL_GREATER, 0.5);
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_CW);

    // TODO(all): remember to replace when add lighting
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
}

void Canvas::run() {
    glutTimerFunc(1000.0/canvas_fps, this->update, 0);
    glutMainLoop();
}

void Canvas::update(int value) {
    //
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    dt = (currentTime - previousTime)/1000;
    previousTime = currentTime;

    //
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    window_resize(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
    glLoadIdentity();

    // TODO(all): Remove
    draw_coords_system();

    //
    for (auto& shape : canvas_shapes) {
        shape->display();
    }

    //
    glutTimerFunc(1000.0/canvas_fps, Canvas::update, 0);

    //
    glutPostRedisplay();
    glutSwapBuffers();
}

void Canvas::subscription(std::shared_ptr<Shape> shape) {
    canvas_shapes.push_back(shape);
}
