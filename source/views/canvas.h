#ifndef SOURCE_VIEWS_CANVAS_H_
#define SOURCE_VIEWS_CANVAS_H_

#include <GL/gl.h>
#include <vector>
#include <memory>
#include "../utils/shapes/shape.h"
#include "../utils/style/color.h"

class Canvas {
    public:
        //
        Canvas(
            GLuint width, GLuint height,
            const GLchar* name, GLuint fps = 60);

        //
        void init();

        //
        void run();

        //
        static void update(int value);

        //
        void subscription(std::shared_ptr<Shape> shape);
        void unsubscription(std::shared_ptr<Shape> shape);
};

#endif  // SOURCE_VIEWS_CANVAS_H_
