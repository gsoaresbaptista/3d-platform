#ifndef SOURCE_UTILS_GAMESHAPES_PLANE_H_
#define SOURCE_UTILS_GAMESHAPES_PLANE_H_

#include "../shapes/3d/box.h"
#include "../style/texture.h"

class Plane: public Box {
    public:
        GLfloat width;
        GLfloat depth;
        GLuint coord;

    public:
        Plane(
            vec3 center, GLfloat width, GLfloat depth,
            BoxType type = BoxType::DEEPSLATE_BRICKS,
            GLuint coord = 0);
        void draw_block(GLfloat block_size, GLenum mode = GL_FILL);
};

#endif  // SOURCE_UTILS_GAMESHAPES_PLANE_H_
