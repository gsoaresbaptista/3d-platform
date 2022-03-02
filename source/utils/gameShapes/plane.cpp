#include "plane.h"
#include "../shapes/2d/rectangle.h"
#include "../others/gameConstants.h"

Plane::Plane(
        vec3 p0, vec3 p1, vec3 p2, vec3 p3, BoxType type, vec3 center)
        : Shape(center) {
    this->type = type;
    this->p0 = p0, this->p1 = p1, this->p2 = p2, this->p3  = p3;
}

void Plane::draw_block(GLfloat block_size, GLenum mode) {
    // vec3 p0, p1, p2, p3;

    glNewList(this->id_, GL_COMPILE);
        glPolygonMode(GL_FRONT, mode);

        // switch (coord) {
        // case 0:
        //     p0 = vec3(-width/2.0, center.y, -depth/2.0);
        //     p1 = vec3(-width/2.0, center.y, depth/2.0);
        //     p2 = vec3(width/2.0, center.y, depth/2.0);
        //     p3 = vec3(width/2.0, center.y, -depth/2.0);
        //     break;
        // case 1:
        //     p0 = vec3(width/2.0, center.y, -depth/2.0);
        //     p1 = vec3(width/2.0, center.y, depth/2.0);
        //     p2 = vec3(-width/2.0, center.y, depth/2.0);
        //     p3 = vec3(-width/2.0, center.y, -depth/2.0);
        //     break;
        // case 2:
        //     p0 = vec3(-width/2.0, -depth/2.0, center.z);
        //     p1 = vec3(-width/2.0, depth/2.0, center.z);
        //     p2 = vec3(width/2.0, depth/2.0, center.z);
        //     p3 = vec3(width/2.0, -depth/2.0, center.z);
        //     break;
        // case 3:
        //     p0 = vec3(width/2.0, -depth/2.0, center.z);
        //     p1 = vec3(width/2.0, depth/2.0, center.z);
        //     p2 = vec3(-width/2.0, depth/2.0, center.z);
        //     p3 = vec3(-width/2.0, -depth/2.0, center.z);
        //     break;
        // case 4:
        //     p3 = vec3(center.x, depth/2.0, -width/2.0);
        //     p2 = vec3(center.x, -depth/2.0, -width/2.0);
        //     p1 = vec3(center.x, -depth/2.0, width/2.0);
        //     p0 = vec3(center.x, depth/2.0, width/2.0);
        //     break;
        // case 5:
        //     p0 = vec3(center.x, depth/2.0, -width/2.0);
        //     p1 = vec3(center.x, -depth/2.0, -width/2.0);
        //     p2 = vec3(center.x, -depth/2.0, width/2.0);
        //     p3 = vec3(center.x, depth/2.0, width/2.0);
        //     break;
        // }
        Rectangle::draw_block(
            p0, p1, p2, p3, block_size, RED, Outline::SPLITTED, type);
    glEndList();
}

void Plane::draw(std::shared_ptr<Texture>, GLenum mode, Outline outline) {
    //
}
