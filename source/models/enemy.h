#ifndef SOURCE_MODELS_ENEMY_H_
#define SOURCE_MODELS_ENEMY_H_

#include "player.h"
#include "../utils/shapes/3d/box.h"

class Enemy: public Player {
    private:
        void display_character();
        std::shared_ptr<Shape> platform;
        vec3 move_dir;
        float move_time;

    public:
        Enemy(vec3 center, GLfloat height);
        ~Enemy();

        void draw(
            std::shared_ptr<Texture> texture = nullptr,
            GLenum mode = GL_FILL,
            Outline outline = Outline::SPLITTED);

        void set_platform(std::shared_ptr<Shape> box);
        bool out_platform(vec3 movement);
        void set_movement(vec3 dir, float time);
        void move(float dt, float speed);
        vec3 get_move_dir();
};

#endif  // SOURCE_MODELS_ENEMY_H_
