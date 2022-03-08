#include "torch.h"
#include "../style/color.h"
#include "../math/math.h"
#include "../shapes/2d/rectangle.h"

Torch::Torch(vec3 center) {
    //
    this->center = center;
    this->flame_size = random_float(0, 0.5);
    this->accumulated_time = 0;
}

void Torch::draw_block(GLfloat block_size, GLenum mode) {
    this->block_size = block_size;
    this->center.z -= block_size*0.9;
    this->width = block_size*0.125;
    this->height = block_size*0.625;
    this->depth = block_size*0.125;
    this->type = BoxType::TORCH;

    //
    vec3 p0(-block_size/2, +block_size/2, -block_size/2);
    vec3 p1(-block_size/2, -block_size/2, -block_size/2);
    vec3 p2(block_size/2, -block_size/2, -block_size/2);
    vec3 p3(block_size/2, +block_size/2, -block_size/2);
    vec3 nc(center.x, center.y, center.z + block_size*0.7);
    this->flame = std::make_shared<Plane>(p0, p1, p2, p3, vec3(0, 0, 1), BoxType::FLAME, nc);

    this->flame->draw_block(block_size, mode);
    // Box::draw_block(block_size, mode);
}

void Torch::update_frame(float dt) {
    this->accumulated_time += dt;

    if (accumulated_time >= 0.01666) {
        this->accumulated_time = 0;
        this->flame_size -= 0.01;
        if (this->flame_size <= 0)
            this->flame_size = 0.5;
    }
}

void Torch::display(float dt, std::shared_ptr<ControllerData> controller) {
    glPushMatrix();
        glPushMatrix();
            this->flame->translate();
            glTranslatef(0, block_size/2, -block_size/3 - flame_size/2);
            glScalef(flame_size, flame_size, flame_size);
            glRotatef(controller->to_rotate.x, 0, 1, 0);
            this->flame->display(dt);
        glPopMatrix();
        this->translate();
        glRotatef(45, 1, 0, 0);
        // glCallList(this->id_);

            vec3 p0(-width/2.0, height/2.0, depth/2.0);
            vec3 p1(-width/2.0, -height/2.0, depth/2.0);
            vec3 p2(width/2.0, -height/2.0, depth/2.0);
            vec3 p3(width/2.0, height/2.0, depth/2.0);

            // Back
            vec3 p4(width/2.0, height/2.0, -depth/2.0);
            vec3 p5(width/2.0, -height/2.0, -depth/2.0);
            vec3 p6(-width/2.0, -height/2.0, -depth/2.0);
            vec3 p7(-width/2.0, height/2.0, -depth/2.0);
            glNormal3f(0, 0, 1);
            Rectangle::draw_block(  // Frente
                p0, p1, p2, p3, block_size, WHITE, Outline::ENTIRE, type);

            glNormal3f(1, 0, 0);
            Rectangle::draw_block(  // Direita
                p3, p2, p5, p4, block_size, WHITE, Outline::ENTIRE, type);

            glNormal3f(0, 0, -1);
            Rectangle::draw_block(  // Trás
                p4, p5, p6, p7, block_size, WHITE, Outline::ENTIRE, type);

            glNormal3f(-1, 0, 0);
            Rectangle::draw_block(  // Esquerda
                p7, p6, p1, p0, block_size, WHITE, Outline::ENTIRE, type);

            glNormal3f(0, 1, 0);
            Rectangle::draw_block(  // Cima
                p7, p0, p3, p4, block_size, WHITE, Outline::ENTIRE, type);

            glNormal3f(0, -1, 0);
            Rectangle::draw_block(  // Baixo
                p1, p6, p5, p2, block_size, WHITE, Outline::ENTIRE, type);
    glPopMatrix();
    update_frame(dt);
}
