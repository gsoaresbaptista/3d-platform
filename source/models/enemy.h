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
        float shoot_time;

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
        float get_shoot_time();
        void increment_shoot(float dt);
        void set_angles(float yaw0, float yaw1, float pitch0, float pitch1);
};

#endif  // SOURCE_MODELS_ENEMY_H_
