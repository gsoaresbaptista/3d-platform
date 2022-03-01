#include "chain.h"
#include "../2d/rectangle.h"
#include "../../others/gameConstants.h"

Chain::Chain(vec3 center, GLfloat width, GLfloat height, GLfloat depth)
    : Box(center, width, height, depth, BoxType::CHAIN) {
    this->width = width;
    this->height = height;
    this->depth = depth;
    this->type = type;
}

void Chain::draw_block(GLfloat block_size, GLenum mode) {
    vec3 p0(-width/2.0, height/2.0, depth/2.0);
    vec3 p1(-width/2.0, -height/2.0, depth/2.0);
    vec3 p2(width/2.0, -height/2.0, depth/2.0);
    vec3 p3(width/2.0, height/2.0, depth/2.0);

    glNewList(this->id_, GL_COMPILE);
        glPolygonMode(GL_FRONT, mode);
        glDisable(GL_CULL_FACE);
        CHAIN_TEX->bind();
        glPushMatrix();
            glRotatef(-45, 0, 1, 0);
            glTranslated(width/2.f, 0, 0);
            glBegin(GL_QUADS);
                glTexCoord2f(0, 0);
                glVertex3fv(&p0.x);
                glTexCoord2f(0, height/(block_size));
                glVertex3fv(&p1.x);
                glTexCoord2f(0.1875, height/block_size);
                glVertex3fv(&p2.x);
                glTexCoord2f(0.1875, 0);
                glVertex3fv(&p3.x);
            glEnd();
        glPopMatrix();

        glPushMatrix();
            glRotatef(45, 0, 1, 0);
            glTranslated(-width/2.f, 0, 0);
            glBegin(GL_QUADS);
                glTexCoord2f(0.1875, 0);
                glVertex3fv(&p0.x);
                glTexCoord2f(0.1875, height/(block_size));
                glVertex3fv(&p1.x);
                glTexCoord2f(2*0.1875, height/block_size);
                glVertex3fv(&p2.x);
                glTexCoord2f(2*0.1875, 0);
                glVertex3fv(&p3.x);
            glEnd();
        glPopMatrix();
        CHAIN_TEX->unbind();
        glEnable(GL_CULL_FACE);
    glEndList();
}
