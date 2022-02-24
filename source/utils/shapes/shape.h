#ifndef SOURCE_UTILS_SHAPES_SHAPE_H_
#define SOURCE_UTILS_SHAPES_SHAPE_H_

#include <cstdio>
#include <memory>
#include "../linear/vec3.h"
#include "../style/color.h"
#include "../style/texture.h"

enum class Outline { SPLITTED = 0, ENTIRE = 1};

class Shape {
    protected:
        vec3 center;
        GLuint id_;

    public:
        explicit Shape(vec3 center) {
            this->center = center;
            this->id_ = glGenLists(1);
        }

        GLuint getID() {
            return this->id_;
        }

        void translate() {
            glTranslatef(center.x, center.y, center.z);
        }

        ~Shape() {
            glDeleteLists(this->id_, 1);
        }

        virtual void draw(
                std::shared_ptr<Texture> texture = nullptr,
                GLenum mode = GL_FILL,
                Outline outline = Outline::SPLITTED) = 0;
};

#endif  // SOURCE_UTILS_SHAPES_SHAPE_H_
