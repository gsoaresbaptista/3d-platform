#ifndef SOURCE_UTILS_SHAPES_2D_RECTANGLE_H_
#define SOURCE_UTILS_SHAPES_2D_RECTANGLE_H_

#include "../shape.h"
#include "../../linear/vec2.h"
#include "../../linear/vec3.h"

class Rectangle: public Shape {
    public:
        // Draw rectangle from contour points
        static void draw(
            vec3 p0, vec3 p1, vec3 p2, vec3 p3,
            GLuint n_segs = 4, GLuint n_stacks = 2,
            Color color = RED,
            Outline outline = Outline::SPLITTED,
            bool repeat_texture = false);

        // Draw rectangle from contour points and texture boundaries
        static void draw(
            vec3 p0, vec3 p1, vec3 p2, vec3 p3, vec2 t0, vec2 t2,
            GLuint n_segs = 4, GLuint n_stacks = 2,
            Color color = RED,
            Outline outline = Outline::SPLITTED);

        // Draw rectangle from contour points and texture contour
        static void draw(
            vec3 p0, vec3 p1, vec3 p2, vec3 p3,
            vec2 t0, vec2 t1, vec2 t2, vec2 t3,
            GLuint n_segs = 4, GLuint n_stacks = 2,
            Color color = RED,
            Outline outline = Outline::ENTIRE,
            bool repeat_texture = false);
};

#endif  // SOURCE_UTILS_SHAPES_2D_RECTANGLE_H_
