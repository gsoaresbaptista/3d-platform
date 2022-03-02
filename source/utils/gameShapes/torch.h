#ifndef SOURCE_UTILS_GAMESHAPES_TORCH_H_
#define SOURCE_UTILS_GAMESHAPES_TORCH_H_

#include <GL/gl.h>
#include "../shapes/shape.h"
#include "./plane.h"
#include "../shapes/3d/box.h"
#include "../style/texture.h"
#include "../others/gameConstants.h"
#include "../math/math.h"

class Torch: public Box {
    private:
        GLfloat flame_size;
        GLfloat block_size;
        std::shared_ptr<Plane> flame = nullptr;
        GLfloat accumulated_time;

        void update_frame(float dt);

    public:
        explicit Torch(vec3 center);

        void display(float dt, std::shared_ptr<ControllerData> controller = nullptr);

        //
        void draw_block(GLfloat block_size, GLenum mode = GL_FILL);
};

#endif  // SOURCE_UTILS_GAMESHAPES_TORCH_H_
