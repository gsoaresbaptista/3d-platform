#ifndef SOURCE_MODELS_PLAYER_H_
#define SOURCE_MODELS_PLAYER_H_

#include "../utils/math/math.h"
#include "../utils/shapes/shape.h"
#include "../utils/shapes/3d/cylinder.h"

class Player: public Shape {
    private:
        Cylinder* collision_boundary;
        GLfloat height;

    public:
        Player(vec3 center, GLfloat height);

        void draw(
            std::shared_ptr<Texture> texture = nullptr,
            GLenum mode = GL_FILL,
            Outline outline = Outline::SPLITTED);

        void display(float dt);
};

#endif  // SOURCE_MODELS_PLAYER_H_
