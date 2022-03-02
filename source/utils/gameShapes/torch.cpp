#include "torch.h"
#include "../style/color.h"
#include "../shapes/2d/rectangle.h"

Torch::Torch(
        vec3 center, GLfloat width, GLfloat height, GLfloat depth, BoxType type)
        : Box(center, width, height, depth, BoxType::TORCH) {
    //
}

void Torch::draw_block(GLfloat block_size, GLenum mode) {
    Box::draw_block(block_size, mode);
}
