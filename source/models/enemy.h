#ifndef SOURCE_MODELS_ENEMY_H_
#define SOURCE_MODELS_ENEMY_H_

#include "player.h"

class Enemy: public Player {
    public:
        Enemy(vec3 center, GLfloat height);
        ~Enemy();

        void draw(
            std::shared_ptr<Texture> texture = nullptr,
            GLenum mode = GL_FILL,
            Outline outline = Outline::SPLITTED);

        void display(float dt);
        void display_character();
};

#endif  // SOURCE_MODELS_ENEMY_H_
