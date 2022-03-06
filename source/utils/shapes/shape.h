#ifndef SOURCE_UTILS_SHAPES_SHAPE_H_
#define SOURCE_UTILS_SHAPES_SHAPE_H_

#include <memory>
#include "../../controllers/controllerData.h"
#include "../math/math.h"
#include "../style/color.h"
#include "../style/texture.h"

enum class Outline { SPLITTED = 0, ENTIRE = 1};

class Shape {
    protected:
        vec3 center;
        GLuint id_;

    public:
        Shape() { }

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

        virtual void display(
            float dt, std::shared_ptr<ControllerData> controller) {
            this->display(dt);
        }

        virtual void display(float dt) {
            glPushMatrix();
                glCallList(this->id_);
            glPopMatrix();
        }

        // TODO (=0)
        virtual GLfloat get_width() {}
        virtual GLfloat get_height() {}
        virtual GLfloat get_depth() {}

        vec3 get_center() {
            return this->center;
        }

        virtual void draw(
                std::shared_ptr<Texture> texture = nullptr,
                GLenum mode = GL_FILL,
                Outline outline = Outline::SPLITTED) = 0;

        virtual void draw_block(GLfloat block_size, GLenum mode) {}
};

#endif  // SOURCE_UTILS_SHAPES_SHAPE_H_
