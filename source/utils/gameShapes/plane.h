#ifndef SOURCE_UTILS_GAMESHAPES_PLANE_H_
#define SOURCE_UTILS_GAMESHAPES_PLANE_H_

#include "../shapes/shape.h"
#include "../others/gameConstants.h"

#include "../style/texture.h"

class Plane: public Shape {
    protected:
        BoxType type;
        vec3 p0, p1, p2, p3;

    public:
        Plane();

        Plane(
            vec3 p0, vec3 p1, vec3 p2, vec3 p3,
            BoxType type = BoxType::DEEPSLATE_BRICKS,
            vec3 center = vec3(0, 0, 0));

        void draw(
            std::shared_ptr<Texture> = nullptr,
            GLenum mode = GL_FILL,
            Outline outline = Outline::ENTIRE);

        void draw_block(GLfloat block_size, GLenum mode = GL_FILL);

        GLfloat get_width();
        GLfloat get_height();
        GLfloat get_depth();
};

#endif  // SOURCE_UTILS_GAMESHAPES_PLANE_H_
