#ifndef SOURCE_UTILS_SHAPES_2D_CIRCLE_H_
#define SOURCE_UTILS_SHAPES_2D_CIRCLE_H_

#include "../shape.h"

class Circle: public Shape {
    public:
        // Draw a circle from the radius and number of points sampled
        static void draw(
            GLfloat radius,
            GLuint n_segs = 1,
            Color color = RED,
            Outline outline = Outline::SPLITTED);
};

#endif  // SOURCE_UTILS_SHAPES_2D_CIRCLE_H_
