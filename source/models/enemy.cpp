#include "enemy.h"
#include "../utils/style/skeleton.h"

Enemy::Enemy(vec3 center, GLfloat height) : Player(center, height) {
    this->center = center;
    this->coordinateSystem->direction = vec3(0, 0, 1);
    this->platform = nullptr;
    this->move_dir = coordinateSystem->direction;
    this->move_time = 0;
    this->shoot_time = random_float(0, 1) * 7 + 1;
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

void Enemy::increment_shoot(float dt) {
    if (dt < 0) {
        this->shoot_time = random_float(0, 1) * 7 + 1;
    } else {
        this->shoot_time -= dt;
    }
}

void Enemy::set_angles(float yaw0, float yaw1, float pitch0, float pitch1) {
    this->coordinateSystem->yaw = -90 - atan2(yaw0, yaw1) * 180/M_PI;
    this->coordinateSystem->pitch = 180 - atan2(pitch0, pitch1) * 180/M_PI;
}

void Enemy::display_character() {
    glPushMatrix();
        glTranslatef(0, -dheight *1.25, 0);
        glRotatef(180, 0, 1, 0);
        // glRotatef(this->coordinateSystem->yaw, 0, 1, 0);

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

void Enemy::set_platform(std::shared_ptr<Shape> box) {
    if (platform == nullptr) {
        vec3 c = box->get_center();
        this->platform = box;
        this->set_y(c.y + box->get_height() + dheight*2);
    }
}

bool Enemy::out_platform(vec3 movement) {
    if (platform != nullptr) {
        float width = platform->get_width()/2.f;
        float height = platform->get_height()/2.f;
        float depth = platform->get_depth()/2.f;
        vec3 center = platform->get_center();

        vec3 np = this->get_position() + this->get_center() + movement;

        if ((np.z - dheight <= center.z - depth) ||
            (np.z + dheight >= center.z + depth) ||
            (np.x - dheight <= center.x - width) ||
            (np.x + dheight >= center.x + width)) {
            return true;
        }

        return false;
    }
    return false;
}

void Enemy::set_movement(vec3 dir, float time) {
    this->move_dir = dir;
    this->move_time = time;
}

void Enemy::move(float dt, float speed) {
    move_time -= dt;

    if (this->move_time <= 0) {
        float random = random_float(0, 1);
        this->move_time = random * 3 + 1;

        if (random <= 0.25) {
            this->move_dir = vec3(1, 0, 0);
        } else if (random <= 0.50) {
            this->move_dir = vec3(-1, 0, 0);
        } else if (random <= 0.75) {
            this->move_dir = vec3(0, 0, 1);
        } else {
            this->move_dir = vec3(0, 0, -1);
        }

        if ((this->move_dir != this->coordinateSystem->direction)) {
            //
            this->coordinateSystem->direction = move_dir;
            this->coordinateSystem->up = vec3(0, 1, 0);
            this->coordinateSystem->left = vec3(0, 1, 0) * move_dir;

            if (move_dir == vec3(0, 0, 1)) {
                this->coordinateSystem->yaw = 180;
            } else if (move_dir == vec3(0, 0, -1)) {
                this->coordinateSystem->yaw = 0;
            } else if (move_dir == vec3(1, 0, 0)) {
                this->coordinateSystem->yaw = -90;
            } else if (move_dir == vec3(-1, 0, 0)) {
                this->coordinateSystem->yaw = 90;
            }
        }
    }
}

void Enemy::set_pitch(float pitch) {
    this->coordinateSystem->pitch = pitch;
}

vec3 Enemy::get_move_dir() {
    return this->move_dir;
}

float Enemy::get_shoot_time() {
    return this->shoot_time;
}

std::shared_ptr<Enemy> Enemy::clone() {
    auto cloned_enemy = std::make_shared<Enemy>(center, height);

    return cloned_enemy;
}