#ifndef SOURCE_UTILS_SHAPES_2D_CIRCLE_H_
#define SOURCE_UTILS_SHAPES_2D_CIRCLE_H_

#include "../shape.h"

class Circle: public Shape {
    private:
        GLfloat radius;

    public:
        Circle(vec2 center, GLfloat radius);
        void draw(Color color = RED);
};

#endif  // SOURCE_UTILS_SHAPES_2D_CIRCLE_H_
