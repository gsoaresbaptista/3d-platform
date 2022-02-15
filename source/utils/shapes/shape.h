#ifndef SOURCE_UTILS_SHAPES_SHAPE_H_
#define SOURCE_UTILS_SHAPES_SHAPE_H_

#include <cstdio>
#include <memory>
#include "../linear/vec2.h"
#include "../style/color.h"


class Shape {
    private:
        vec2 center;

    public:
        // Shape() {
            // this->center = vec2(0, 0);
        // }

        explicit Shape(vec2 center) {
            this->center = center;
        }

        virtual void draw(Color color = RED) { printf("BASE SHAPE!\n"); }
};

#endif  // SOURCE_UTILS_SHAPES_SHAPE_H_
