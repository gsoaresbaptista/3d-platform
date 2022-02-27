#ifndef SOURCE_UTILS_OTHERS_SVGREADER_H_
#define SOURCE_UTILS_OTHERS_SVGREADER_H_

#include <vector>
#include <memory>
// #include "../shapes/2d/rectangle.h"
#include "../shapes/3d/box.h"
#include "../shapes/2d/circle.h"
#include "../libs/tinyxml2.h"

using namespace tinyxml2;
using std::vector;

// Classe para leitor de svg
// class SVGReader {
//     XMLDocument svg;

//     public:
//         SVGReader(const char* pFilename);
//         vector<Circle> getCircles();
//         vector<Rectangle> getRects();
// };

struct SVGReader {
    // std::vector<Circle> circles;
    std::vector<std::shared_ptr<Box>> rects;
    float arena_width;
    float arena_height;
    float arena_depth;
    float arena_x;
    float arena_y;
    float block_size;
};

std::shared_ptr<SVGReader> readSVG(const char* file_path);

#endif  // SOURCE_UTILS_OTHERS_SVGREADER_H_
