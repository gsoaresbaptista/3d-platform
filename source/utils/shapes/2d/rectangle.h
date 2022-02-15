#ifndef SOURCE_UTILS_SHAPES_2D_RECTANGLE_H_
#define SOURCE_UTILS_SHAPES_2D_RECTANGLE_H_

#include "../shape.h"

class Rectangle: public Shape {
    private:
        GLfloat width;
        GLfloat height;

    public:
        Rectangle(vec2 center, GLfloat width, GLfloat height);
        void draw(Color color = RED);
};

#endif  // SOURCE_UTILS_SHAPES_2D_RECTANGLE_H_
