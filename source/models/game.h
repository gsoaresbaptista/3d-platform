#ifndef SOURCE_MODELS_GAME_H_
#define SOURCE_MODELS_GAME_H_

#include <vector>
#include <memory>
#include "player.h"
#include "../utils/shapes/shape.h"
#include "../utils/shapes/3d/box.h"
#include "../utils/others/SVGReader.h"
#include "../utils/math/math.h"
#include "../controllers/controller.h"
#include "../utils/style/texture.h"

class Game: public Shape {
    private:
        GLuint obstacles_id;
        GLfloat block_size;
        std::vector<std::shared_ptr<Shape>> obstacles;
        std::shared_ptr<ControllerData> controller;
        std::shared_ptr<SVGData> data;
        Player* player;
        GLuint current_camera;
        GLfloat player_speed;
        GLfloat player_jump_speed;
        // std::vector<Enemy> enemies;

        //
        void update(float dt);
        void update_player_move(float dt);
        void update_player_jump(float dt);
        void gravity(float dt);
        bool x_obstacle_collision(float dt, GLfloat x_player, GLfloat radius, std::shared_ptr<Shape> obstacle);
        bool y_obstacle_collision(GLfloat head_player, GLfloat feet_player, std::shared_ptr<Shape> obstacle);
        bool lateral_collision(float dt);
        bool floor_collision_obstacle(float dt);

    public:
        Game(
            std::shared_ptr<SVGData> data,
            std::shared_ptr<ControllerData> cData);

        void draw(
                std::shared_ptr<Texture> texture = nullptr,
                GLenum mode = GL_FILL,
                Outline outline = Outline::SPLITTED);


        void display(float dt);
};

#endif  // SOURCE_MODELS_GAME_H_
