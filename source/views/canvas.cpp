#include "canvas.h"
#include <GL/glut.h>

GLuint canvas_width;
GLuint canvas_height;
GLuint canvas_id;
std::vector<Shape*> canvas_shapes;

Canvas::Canvas(GLuint width, GLuint height, std::string name) {
    canvas_width = width;
    canvas_height = height;
    this->width = width;
    this->height = height;
    this->name = name;
}

void Canvas::init() {
    int argc = 1;
    glutInit(&argc, NULL);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(this->width, this->height);
    this->id_ = glutCreateWindow(this->name.c_str());
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

void Canvas::run() {
    glutDisplayFunc(this->update);
    glutMainLoop();
}

void Canvas::update() {
    glClear(GL_COLOR_BUFFER_BIT);

    for (auto& shape : canvas_shapes) {
        shape->draw();
    }

    glutPostRedisplay();
    glutSwapBuffers();
}

void Canvas::subscription(Shape* shape) {
    canvas_shapes.push_back(shape);
}
