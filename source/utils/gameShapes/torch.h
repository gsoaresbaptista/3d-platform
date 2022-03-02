#ifndef SOURCE_UTILS_GAMESHAPES_TORCH_H_
#define SOURCE_UTILS_GAMESHAPES_TORCH_H_

#include <GL/gl.h>
#include "../shapes/shape.h"
#include "../shapes/3d/box.h"
#include "../style/texture.h"
#include "../others/gameConstants.h"
#include "../math/math.h"

class Torch: public Box {
    public:
        GLfloat width;
        GLfloat height;
        GLfloat depth;

    public:
        Torch(
            vec3 center,
            GLfloat width, GLfloat height, GLfloat depth,
            BoxType type = BoxType::DEEPSLATE_BRICKS);

        // void display(float dt);

        //
        void draw_block(GLfloat block_size, GLenum mode = GL_FILL);
};

#endif  // SOURCE_UTILS_GAMESHAPES_TORCH_H_
