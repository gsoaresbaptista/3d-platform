#ifndef SOURCE_UTILS_OTHERS_SVGREADER_H_
#define SOURCE_UTILS_OTHERS_SVGREADER_H_

#include <vector>
#include <memory>
// #include "../shapes/2d/rectangle.h"
#include "../shapes/3d/box.h"
#include "../shapes/shape.h"
#include "../shapes/2d/circle.h"
#include "../gameShapes/torch.h"
#include "../libs/tinyxml2.h"

using namespace tinyxml2;
using std::vector;

struct SVGData {
    // std::vector<Circle> circles;
    std::vector<std::shared_ptr<Shape>> rects;
    std::vector<std::shared_ptr<Torch>> torchs;
    float arena_width;
    float arena_height;
    float arena_depth;
    float arena_x;
    float arena_y;
    float block_size;
    vec3 player_pos;
};

std::shared_ptr<SVGData> readSVG(const char* file_path);

#endif  // SOURCE_UTILS_OTHERS_SVGREADER_H_
