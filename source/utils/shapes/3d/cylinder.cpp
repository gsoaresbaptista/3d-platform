#include "./cylinder.h"
#include "../../style/color.h"
#include "../2d/circle.h"
#include "../2d/rectangle.h"
#include <cmath>
#include <assert.h>

Cylinder::Cylinder(vec3 center, GLfloat height, GLfloat radius)
         : Shape(center) {
    this->height = height;
    this->radius = radius;
}

void Cylinder::draw(std::shared_ptr<Texture> texture, GLenum mode, Outline outline) {
    Cylinder::draw(10, 10, texture, mode, outline);
}

void Cylinder::draw(
        GLuint n_segs,
        GLuint n_stacks,
        std::shared_ptr<Texture> texture,
        GLenum mode,
        Outline outline) {
    //
    assert((n_segs >= 4) & (n_segs % 2 == 0));

    //
    float delta_h = height/n_stacks;
    float delta_theta = 2*M_PI/n_segs;
    float delta_x = 2*M_PI*radius/(n_segs-1);

    // Draw
    glNewList(this->id_, GL_COMPILE);
        glPolygonMode(GL_FRONT, mode);
        if (texture != nullptr) texture->bind();
        //
        glPushMatrix();
            glTranslatef(0, 0, height/2);
            Circle::draw(this->radius, n_segs, GREEN, outline);
        glPopMatrix();

        //
        glPushMatrix();
            glTranslatef(0, 0, -height/2);
            glRotatef(180, 0, 1, 0);
            Circle::draw(this->radius, n_segs, GREEN, outline);
        glPopMatrix();

        //
        for (int i = 0; i < n_stacks; i++) {
            for (int j = 0; j < n_segs; j++) {
                vec2 t0(j*delta_x, (i+1)*delta_h);
                vec2 t2((j+1)*delta_x, i*delta_h);

                vec3 p0(
                    radius*cosf(j*delta_theta),
                    radius*sinf(j*delta_theta),
                    -height/2 + (i+1)*delta_h);

                vec3 p1(
                    radius*cosf(j*delta_theta),
                    radius*sinf(j*delta_theta),
                    -height/2 + (i)*delta_h);

                vec3 p2(
                    radius*cosf((j+1)*delta_theta),
                    radius*sinf((j+1)*delta_theta),
                    -height/2 + (i)*delta_h);

                vec3 p3(
                    radius*cosf((j+1)*delta_theta),
                    radius*sinf((j+1)*delta_theta),
                    -height/2 + (i+1)*delta_h);

                Rectangle::draw(
                    p0, p1, p2, p3, t0, t2,
                    1, 1, RED, Outline::ENTIRE);
            }
        }

        if (texture != nullptr) texture->unbind();
    glEndList();
}
