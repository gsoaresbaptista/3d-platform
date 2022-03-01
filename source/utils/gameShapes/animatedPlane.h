#ifndef SOURCE_UTILS_GAMESHAPES_ANIMATEDPLANE_H_
#define SOURCE_UTILS_GAMESHAPES_ANIMATEDPLANE_H_

#include "plane.h"
#include "../shapes/3d/box.h"
#include "../style/texture.h"

class AnimatedPlane: public Plane {
    public:
        GLfloat width;
        GLfloat depth;
        GLuint coord;
        GLuint n_frames;
        std::shared_ptr<Texture> sprite;
        GLuint current_sprite;
        GLfloat block_size;
        GLfloat accumulated_time;

    public:
        AnimatedPlane(
            vec3 center, GLfloat width, GLfloat depth,
            std::shared_ptr<Texture> sprite = nullptr,
            GLuint n_frames = 0, GLuint coord = 0);

        void display(float dt);

        void draw_block(GLfloat block_size, GLenum mode = GL_FILL);
};

#endif  // SOURCE_UTILS_GAMESHAPES_ANIMATEDPLANE_H_
