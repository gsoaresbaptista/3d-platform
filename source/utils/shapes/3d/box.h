#ifndef SOURCE_UTILS_SHAPES_3D_BOX_H_
#define SOURCE_UTILS_SHAPES_3D_BOX_H_

#include <GL/gl.h>
#include "../shape.h"
#include "../../style/texture.h"

class Box: public Shape {
    private:
        GLfloat width;
        GLfloat height;
        GLfloat depth;

    public:
        Box(vec3 center, GLfloat width, GLfloat height, GLfloat depth);
        void draw(std::shared_ptr<Texture> texture = nullptr);
};

#endif  // SOURCE_UTILS_SHAPES_3D_BOX_H_
