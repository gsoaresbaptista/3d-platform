#ifndef SOURCE_UTILS_SHAPES_2D_RECTANGLE_H_
#define SOURCE_UTILS_SHAPES_2D_RECTANGLE_H_

#include "../shape.h"

class Rectangle: public Shape {
    private:
        GLfloat width;
        GLfloat height;

    public:
        //
        static void draw(
            GLfloat depth, GLfloat width,
            GLfloat height, Color color);

        //
        static void draw(
            vec3 p0, vec3 p1, vec3 p2,
            vec3 p3, Color color = RED);
};

#endif  // SOURCE_UTILS_SHAPES_2D_RECTANGLE_H_
