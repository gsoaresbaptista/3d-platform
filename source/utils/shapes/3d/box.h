#ifndef SOURCE_UTILS_SHAPES_3D_BOX_H_
#define SOURCE_UTILS_SHAPES_3D_BOX_H_

#include <GL/gl.h>
#include "../shape.h"
#include "../../style/texture.h"

enum class BoxType { DEEPSLATE_BRICKS = 0, WOOD = 1};

class Box: public Shape {
    public:
        GLfloat width;
        GLfloat height;
        GLfloat depth;
        BoxType type;

    public:
        Box(
            vec3 center,
            GLfloat width, GLfloat height, GLfloat depth,
            BoxType type = BoxType::DEEPSLATE_BRICKS);

        //
        GLfloat get_width();
        GLfloat get_height();
        GLfloat get_depth();

        //
        void draw(
            std::shared_ptr<Texture> texture = nullptr,
            GLenum mode = GL_FILL,
            Outline outline = Outline::SPLITTED);

        //
        void draw(
            GLuint n_segs = 4,
            GLuint n_stacks = 2,
            std::shared_ptr<Texture> texture = nullptr,
            GLenum mode = GL_FILL,
            Outline outline = Outline::SPLITTED);

        //
        void draw_block(GLfloat block_size, GLenum mode = GL_FILL);
};

#endif  // SOURCE_UTILS_SHAPES_3D_BOX_H_
