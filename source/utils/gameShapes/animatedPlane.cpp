#include "animatedPlane.h"
#include "../shapes/2d/rectangle.h"
#include "../others/gameConstants.h"

AnimatedPlane::AnimatedPlane(
        vec3 center, GLfloat width, GLfloat depth,
        std::shared_ptr<Texture> sprite, GLuint n_frames,
        GLuint coord) : Plane(center, width, depth, BoxType::PORTAL, coord) {
    this->width = width;
    this->depth = depth;
    this->type = type;
    this->coord = coord;
    this->sprite = this->sprite;
    this->current_sprite = 0;
    this->accumulated_time = 0;
    this->n_frames = n_frames;
}

void AnimatedPlane::draw_block(GLfloat block_size, GLenum mode) {
    this->block_size = block_size;
}

void AnimatedPlane::display(float dt) {
    glPushMatrix();
        this->translate();
        vec3 p0, p1, p2, p3;

        glPolygonMode(GL_FRONT, GL_FILL);
            switch (coord) {
            case 0:
                p0 = vec3(-width/2.0, center.y, -depth/2.0);
                p1 = vec3(-width/2.0, center.y, depth/2.0);
                p2 = vec3(width/2.0, center.y, depth/2.0);
                p3 = vec3(width/2.0, center.y, -depth/2.0);
                break;
            case 1:
                p0 = vec3(width/2.0, center.y, -depth/2.0);
                p1 = vec3(width/2.0, center.y, depth/2.0);
                p2 = vec3(-width/2.0, center.y, depth/2.0);
                p3 = vec3(-width/2.0, center.y, -depth/2.0);
                break;
            case 2:
                p0 = vec3(-width/2.0, -depth/2.0, center.z);
                p1 = vec3(-width/2.0, depth/2.0, center.z);
                p2 = vec3(width/2.0, depth/2.0, center.z);
                p3 = vec3(width/2.0, -depth/2.0, center.z);
                break;
            case 3:
                p0 = vec3(width/2.0, -depth/2.0, center.z);
                p1 = vec3(width/2.0, depth/2.0, center.z);
                p2 = vec3(-width/2.0, depth/2.0, center.z);
                p3 = vec3(-width/2.0, -depth/2.0, center.z);
                break;
            case 4:
                p3 = vec3(center.x, depth/2.0, -width/2.0);
                p2 = vec3(center.x, -depth/2.0, -width/2.0);
                p1 = vec3(center.x, -depth/2.0, width/2.0);
                p0 = vec3(center.x, depth/2.0, width/2.0);
                break;
            case 5:
                p0 = vec3(center.x, depth/2.0, -width/2.0);
                p1 = vec3(center.x, -depth/2.0, -width/2.0);
                p2 = vec3(center.x, -depth/2.0, width/2.0);
                p3 = vec3(center.x, depth/2.0, width/2.0);
                break;
            }

            vec2 t0(current_sprite*(1.0/32.0), 1);
            vec2 t2((current_sprite + 1)*(1.0/32.0), 0);

            Rectangle::draw_block(
                p0, p1, p2, p3, t0, t2, block_size, RED,
                Outline::SPLITTED, type);
    glPopMatrix();

    if (accumulated_time >= 0.01666) {
        this->accumulated_time = 0;
        this->current_sprite++;
        if (this->current_sprite >= n_frames - 1)
            this->current_sprite = 0;
    } else {
        this->accumulated_time += dt;
    }
}
