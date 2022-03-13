#include "enemy.h"
#include "../utils/style/skeleton.h"

Enemy::Enemy(vec3 center, GLfloat height) : Player(center, height) {
    this->center = center;
    this->coordinateSystem->direction = vec3(0, 0, 1);
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

        glTranslatef(0, angles[20]*2.5*dheight, 0);
        glPushMatrix();
            glTranslatef(dheight*0.65, 2*dheight, 0);
             glTranslatef(dheight/4.f, dheight/2.f, 0.0);
            glRotatef(angles[0], 1, 0, 0);
            glRotatef(angles[1], 0, 0, 1);
            glTranslatef(-dheight/4.f, -dheight/2.f, 0.0);
            glRotatef(coordinateSystem->pitch, -1, 0, 0);
            glCallList(arm0);

            glTranslatef(0, -dheight, 0);
            glTranslatef(dheight/4.f, dheight/2.f, -dheight/4.f);
            glRotatef(-angles[2], 1, 0, 0);
            glRotatef(-angles[3], 0, 0, 1);
            glTranslatef(-dheight/4.f, -dheight/2.f, dheight/4.f);
            glCallList(arm1);
            glScalef(dheight/2.25f, dheight/2.25f, dheight/2.25f);
            glRotatef(-90, 0, 0, 1);
            glRotatef(90, 1, 0, 0);
            glTranslatef(-dheight/2.f, 0, dheight/5.f);
            glCallList(BOW_MODEL[bow_state_id]);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-dheight*0.65, 2*dheight, 0);
            glTranslatef(dheight/4.f, dheight/2.f, 0.0);
            glRotatef(angles[4], 1, 0, 0);
            glRotatef(angles[5], 0, 0, 1);
            glTranslatef(-dheight/4.f, -dheight/2.f, 0.0);
            glRotatef(coordinateSystem->pitch, -1, 0, 0);
            glCallList(arm0);

            glTranslatef(0, -dheight, 0);
            glTranslatef(dheight/15.5f, dheight/2.f, -1.5*dheight);
            glRotatef(angles[6], 1, 0, 0);
            glRotatef(angles[7], 0, 0, 1);
            glTranslatef(-dheight/15.5f, -dheight/2.f, 1.5*dheight);
            glCallList(arm1);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0, 2*dheight, 0);
            glCallList(body);
        glPopMatrix();
        glTranslatef(0, -angles[20]*2.5*dheight, 0);

        glPushMatrix();
            glTranslatef(dheight/4.f, dheight/1.999f, 0);
            glTranslatef(0, dheight/2.f, 0);
            glRotatef(angles[8], 1, 0, 0);
            glRotatef(angles[9], 0, 0, 1);
            glTranslatef(0, -dheight/2.f, 0);
            glCallList(leg0);

            glTranslatef(0, -dheight, 0);
            glTranslatef(0, dheight/2.f, 0);
            glRotatef(angles[14], 1, 0, 0);
            glRotatef(angles[15], 0, 0, 1);
            glTranslatef(0, -dheight/2.f, 0);
            glCallList(leg1);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-dheight/4.f, dheight/1.999f, 0);
            glTranslatef(0, dheight/2.f, 0);
            glRotatef(angles[12], 1, 0, 0);
            glRotatef(angles[13], 0, 0, 1);
            glTranslatef(0, -dheight/2.f, 0);
            glCallList(leg0);

            glTranslatef(0, -dheight, 0);
            glTranslatef(0, dheight/1.999f, 0);
            glRotatef(angles[14], 1, 0, 0);
            glRotatef(angles[15], 0, 0, 1);
            glTranslatef(0, -dheight/1.999f, 0);
            glCallList(leg1);
        glPopMatrix();
    glPopMatrix();
}
