#ifndef SOURCE_MODELS_GAME_H_
#define SOURCE_MODELS_GAME_H_

#include <vector>
#include <memory>
#include "player.h"
#include "shoot.h"
#include "../utils/shapes/shape.h"
#include "../utils/gameShapes/plane.h"
#include "../utils/shapes/3d/box.h"
#include "../utils/others/SVGReader.h"
#include "../utils/math/math.h"
#include "../controllers/controller.h"
#include "../utils/style/texture.h"
#include "camera/camera.h"
#include "camera/freeCamera.h"
#include "camera/defaultCamera.h"
#include "camera/orbitalCamera.h"
#include "camera/handCamera.h"

class Game: public Shape {
    private:
        GLuint obstacles_id;
        GLfloat block_size;
        std::vector<std::shared_ptr<Shape>> obstacles;
        std::shared_ptr<ControllerData> controller;
        std::shared_ptr<SVGData> data;
        Player* player;
        Plane crosshair;
        GLfloat player_speed;
        GLfloat player_jump_speed;
        std::vector<std::shared_ptr<Enemy>> enemies;
        std::vector<std::shared_ptr<Shoot>> shoots;

        //
        GLuint current_camera;
        Camera* camera;
        Camera* freeCamera;
        Camera* orbitalCamera;
        Camera* defaultCamera;
        Camera* handCamera;

        //
        void create_lights();
        void create_portal();
        void update(float dt);
        void update_controller(float dt);
        void update_camera_type();
        void update_player_move(float dt);
        void update_player_jump(float dt, Player* player);
        void gravity(float dt, Player* player);
        void display_hud();
        bool obstacle_collision(vec3 movement, Player* player);

    public:
        Game(
            std::shared_ptr<SVGData> data,
            std::shared_ptr<ControllerData> cData);

        void draw(
                std::shared_ptr<Texture> texture = nullptr,
                GLenum mode = GL_FILL,
                Outline outline = Outline::SPLITTED);


        GLfloat get_width();
        GLfloat get_height();
        GLfloat get_depth();

        void display(float dt);
};

#endif  // SOURCE_MODELS_GAME_H_
