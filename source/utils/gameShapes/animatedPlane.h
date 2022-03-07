#ifndef SOURCE_UTILS_GAMESHAPES_ANIMATEDPLANE_H_
#define SOURCE_UTILS_GAMESHAPES_ANIMATEDPLANE_H_

#include "plane.h"
#include "../shapes/3d/box.h"
#include "../style/texture.h"

class AnimatedPlane: public Plane {
    private:
        GLuint n_frames;
        std::shared_ptr<Texture> sprite;
        GLuint current_sprite;
        GLfloat block_size;
        GLfloat accumulated_time;

        void update_frame(float dt);

    public:
        AnimatedPlane(
            vec3 p0, vec3 p1, vec3 p2, vec3 p3,
            vec3 normal, vec3 center,
            std::shared_ptr<Texture> sprite = nullptr,
            GLuint n_frames = 0);

        void display(float dt);

        void draw_block(GLfloat block_size, GLenum mode = GL_FILL);
};

#endif  // SOURCE_UTILS_GAMESHAPES_ANIMATEDPLANE_H_
