#ifndef SOURCE_VIEWS_CANVAS_H_
#define SOURCE_VIEWS_CANVAS_H_

#include <GL/gl.h>
#include <string>
#include <vector>
#include <memory>

//
#include "../utils/style/color.h"
#include "../utils/shapes/shape.h"

class Canvas {
    private:
        GLuint width;
        GLuint height;
        std::string name;
        GLuint id_;

    public:
        //
        Canvas(GLuint width, GLuint height, std::string name);

        //
        void init();

        //
        void run();

        //
        static void update();

        //
        void subscription(Shape* shape);
        void unsubscription(Shape* shape);
};

#endif  // SOURCE_VIEWS_CANVAS_H_
