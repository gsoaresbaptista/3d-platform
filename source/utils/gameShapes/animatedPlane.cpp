#include "animatedPlane.h"
#include "../shapes/2d/rectangle.h"
#include "../others/gameConstants.h"

AnimatedPlane::AnimatedPlane(
        vec3 p0, vec3 p1, vec3 p2, vec3 p3, std::shared_ptr<Texture> sprite,
        GLuint n_frames)
        : Plane(p0, p1, p2, p3, BoxType::PORTAL) {
    this->sprite = this->sprite;
    this->current_sprite = 0;
    this->accumulated_time = 0;
    this->n_frames = n_frames;
}

void AnimatedPlane::draw_block(GLfloat block_size, GLenum mode) {
    this->block_size = block_size;
}

void AnimatedPlane::update_frame(float dt) {
    this->accumulated_time += dt;

    if (accumulated_time >= 0.01666) {
        this->accumulated_time = 0;
        this->current_sprite++;
        if (this->current_sprite >= n_frames - 1)
            this->current_sprite = 0;
    }
}

void AnimatedPlane::display(float dt) {
    glPushMatrix();
        glPolygonMode(GL_FRONT, GL_FILL);
            vec2 t0(current_sprite*(1.0/n_frames), 1);
            vec2 t2((current_sprite + 1)*(1.0/n_frames), 0);

            Rectangle::draw_block(
                p0, p1, p2, p3, t0, t2, block_size, RED,
                Outline::SPLITTED, type);
    glPopMatrix();

    this->update_frame(dt);
}
