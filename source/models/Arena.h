#ifndef SOURCE_MODELS_ARENA_H_
#define SOURCE_MODELS_ARENA_H_

#include <vector>
#include <memory>
#include "../utils/shapes/shape.h"
#include "../utils/shapes/3d/box.h"
#include "../utils/others/SVGReader.h"
#include "../utils/linear/vec3.h"
#include "../utils/style/texture.h"

class Arena: public Shape {
    private:
        GLuint obstacles_id;
        GLfloat block_size;
        std::vector<std::shared_ptr<Box>> obstacles;
        // std::vector<Enemy> enemies;
        std::shared_ptr<Texture> stone = nullptr;

    public:
        explicit Arena(std::shared_ptr<SVGReader> data);

        void draw(
                std::shared_ptr<Texture> texture = nullptr,
                GLenum mode = GL_FILL,
                Outline outline = Outline::SPLITTED);

        void display();
};

#endif  // SOURCE_MODELS_ARENA_H_
