#include "rectangle.h"
#include "../../linear/vec3.h"
#include <iostream>

void Rectangle::draw(vec3 p0, vec3 p1, vec3 p2, vec3 p3, Color color) {
    glColor3fv(color);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 1.0);
        glVertex3fv(&p0.x);

        glTexCoord2f(0.0, 0.0);
        glVertex3fv(&p1.x);

        glTexCoord2f(1.0, 0.0);
        glVertex3fv(&p2.x);

        glTexCoord2f(1.0, 1.0);
        glVertex3fv(&p3.x);
    glEnd();
}


void Rectangle::draw(
        GLfloat depth, GLfloat width,
        GLfloat height, Color color) {
    //
    vec3 p0(-width/2.0, height/2.0, depth);
    vec3 p1(-width/2.0, -height/2.0, depth);
    vec3 p2(width/2.0, -height/2.0, depth);
    vec3 p3(width/2.0, height/2.0, depth);

    glColor3fv(color);

    glBegin(GL_QUADS);
        glVertex3fv(&p0.x);
        glVertex3fv(&p1.x);
        glVertex3fv(&p2.x);
        glVertex3fv(&p3.x);
    glEnd();
}
