#ifndef SOURCE_UTILS_SHAPES_3D_CYLINDER_H_
#define SOURCE_UTILS_SHAPES_3D_CYLINDER_H_

#include <GL/gl.h>
#include "../shape.h"
#include "../../style/texture.h"

class Cylinder: public Shape {
    private:
        GLfloat height;
        GLfloat radius;

    public:
        Cylinder(vec3 center, GLfloat height, GLfloat radius);

        void draw(
            std::shared_ptr<Texture> texture = nullptr,
            GLenum mode = GL_FILL,
            Outline outline = Outline::SPLITTED);

        void draw(
            GLuint n_segs = 10,
            GLuint n_stacks = 10,
            std::shared_ptr<Texture> texture = nullptr,
            GLenum mode = GL_FILL,
            Outline outline = Outline::SPLITTED);
};

#endif  // SOURCE_UTILS_SHAPES_3D_CYLINDER_H_
