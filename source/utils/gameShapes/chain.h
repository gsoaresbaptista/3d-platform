#ifndef SOURCE_UTILS_GAMESHAPES_CHAIN_H_
#define SOURCE_UTILS_GAMESHAPES_CHAIN_H_

#include "../shapes/3d/box.h"
#include "../style/texture.h"

class Chain: public Box {
    public:
        GLfloat width;
        GLfloat height;
        GLfloat depth;

    public:
        Chain(vec3 center, GLfloat width, GLfloat height, GLfloat depth);

        void draw_block(GLfloat block_size, GLenum mode = GL_FILL);
};

#endif  // SOURCE_UTILS_GAMESHAPES_CHAIN_H_
