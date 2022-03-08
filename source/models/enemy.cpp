#include "enemy.h"
#include "../utils/style/skeleton.h"

Enemy::Enemy(vec3 center, GLfloat height) : Player(center, height) {
    this->center = center;
}

Enemy::~Enemy() {
}

void Enemy::draw(
    std::shared_ptr<Texture> texture,
    GLenum mode, Outline outline) {
    skeleton::draw_head(head, dheight);
    skeleton::draw_body(body, dheight);
    skeleton::draw_arm(arm0, arm1, dheight);
    skeleton::draw_leg(leg0, leg1, dheight);
    this->collision_boundary->draw(30, 10, nullptr, GL_LINE, Outline::ENTIRE);
}

void Enemy::display_character() {
    glPushMatrix();
        glTranslatef(0, -dheight *1.25, 0);
        glPushMatrix();
            glTranslatef(0, 3*dheight, 0);
            glCallList(head);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-dheight*0.65, 2*dheight, 0);
            glCallList(arm0);
            glTranslatef(0, -dheight, 0);
            glCallList(arm1);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(dheight*0.65, 2*dheight, 0);
            glCallList(arm0);
            glTranslatef(0, -dheight, 0);
            glCallList(arm1);
            glRotatef(-90, 0, 0, 1);
            glRotatef(90, 1, 0, 0);
            glTranslatef(-dheight/2.f, 0, dheight/5.f);
            glCallList(BOW_MODEL);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0, 2*dheight, 0);
            glCallList(body);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(dheight/4.f, -dheight/1.999f, 0);
            glCallList(leg1);
            glTranslatef(0, dheight, 0);
            glCallList(leg0);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-dheight/4.f, -dheight/1.999f, 0);
            glCallList(leg1);
            glTranslatef(0, dheight, 0);
            glCallList(leg0);
        glPopMatrix();
    glPopMatrix();
}
