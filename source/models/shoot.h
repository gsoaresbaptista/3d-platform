#ifndef SOURCE_MODELS_SHOOT_H_
#define SOURCE_MODELS_SHOOT_H_

#include "../utils/shapes/shape.h"

class Shoot: Shape {
    private:
        float yaw;
        float pitch;
        float size;
        vec3 direction;
        vec3 position;

    public:
        Shoot(float yaw, float pitch, float size, vec3 center, vec3 direction);

        GLfloat get_width();
        GLfloat get_height();
        GLfloat get_depth();
        vec3 get_direction();
        void set_position(vec3 position);

        void draw(
            std::shared_ptr<Texture> texture = nullptr,
            GLenum mode = GL_FILL,
            Outline outline = Outline::SPLITTED);

        void display(float dt);
        vec3 get_point();
};

#endif  // SOURCE_MODELS_SHOOT_H_
