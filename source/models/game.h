#ifndef SOURCE_MODELS_GAME_H_
#define SOURCE_MODELS_GAME_H_

#include <vector>
#include <memory>
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
        // std::vector<Enemy> enemies;

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
