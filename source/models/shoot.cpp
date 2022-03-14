#include "shoot.h"
#include "../utils/others/gameConstants.h"
#include "../utils/shapes/2d/rectangle.h"

Shoot::Shoot(float yaw, float pitch, float size, vec3 center, vec3 direction) : Shape(center) {
    this->yaw = yaw;
    this->pitch = pitch;
    this->size = size;
    this->direction = direction;
    this->position = vec3(0, 0, 0);
}

GLfloat Shoot::get_width() {
    return 0;
}

GLfloat Shoot::get_height() {
    return 0;
}

GLfloat Shoot::get_depth() {
    return 0;
}

void Shoot::set_position(vec3 position) {
    this->position += position;
}

void Shoot::display(float dt) {
    glPushMatrix();
        float yaw = (73 - this->yaw) * M_PI/180;
        yaw = (yaw < 0) ? fmod(yaw, 73):yaw;

        float pitch = (direction.y*90 + pitch) * M_PI/180;
        vec3 pp = center + vec3(
            -size*cos(yaw)*cos(pitch), size + size*sin(pitch), -size*sin(yaw));

        pp += this->position;

        glTranslatef(pp.x, pp.y, pp.z);
        glRotatef(this->yaw, 0, 1, 0);
        glRotatef(this->pitch, 1, 0, 0);

        glScalef(size/3.f, size/3.f, size/3.f);
        glPushAttrib(GL_ENABLE_BIT);
            glDisable(GL_CULL_FACE);
            glCallList(ARROW_MODEL);
        glPopAttrib();
    glPopMatrix();
}

vec3 Shoot::get_direction() {
    return this->direction;
}

vec3 Shoot::get_point() {
    // Ta errado, mas foi o melhor que deu, coloca com uma
    // margem de erro ai, um raio de acordo com o blocksize
    // em game
    float yaw = (73 - this->yaw) * M_PI/180;
    float pitch = (direction.y*90 + pitch) * M_PI/180;

    vec3 pp = center + vec3(
        -1.75*size*cos(yaw)*cos(pitch),
        size + 1.75*size*sin(pitch),
        -1.75*size*sin(yaw));

    pp += position;

    return pp;
}

void Shoot::draw(
        std::shared_ptr<Texture> texture,
        GLenum mode,
        Outline outline) {
}