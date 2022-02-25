#include "SVGReader.h"
#include "../linear/vec3.h"
#include <iostream>
#include <string.h>

typedef struct {
    float width;
    float height;
    float x;
    float y;
} Rect;

static void normalize_centers() {
}

static void create_boxes(
        std::vector<Rect>* tmp,
        std::vector<std::shared_ptr<Box>>* rects,
        std::shared_ptr<SVGReader> data) {
    for (auto& rect : *tmp) {
        vec3 center = vec3(rect.x, rect.y, data->arena_depth/2.f);
        rects->push_back(std::make_shared<Box>(
            center, rect.width, rect.height, data->arena_depth));
    }
}

// static vector<Circle> get_circles(XMLDocument svg) {
//     vector<Circle> circles;
//     XMLElement* file = svg.FirstChildElement();

//     for (XMLElement* circle = file->FirstChildElement("circle"); circle != NULL; circle = circle->NextSiblingElement("circle")) {
//         float cx, cy, r;

//         circle->QueryFloatAttribute("cx", &cx);
//         circle->QueryFloatAttribute("cy", &cy);
//         circle->QueryFloatAttribute("r", &r);

//         bool isPlayer = !strcmp(circle->Attribute("fill"), "green");

//         Circle circ(cx, cy, r, isPlayer);

//         circles.push_back(circ);
//     }

//     return circles;
// }

static void get_rects(std::shared_ptr<SVGReader> data, XMLDocument* svg) {
    vector<Rect> tmp;
    XMLElement* file = svg->FirstChildElement();
    XMLElement* rect = file->FirstChildElement("rect");

    for (; rect != NULL; rect = rect->NextSiblingElement("rect")) {
        float width, height, x, y;

        rect->QueryFloatAttribute("width", &width);
        rect->QueryFloatAttribute("height", &height);
        rect->QueryFloatAttribute("x", &x);
        rect->QueryFloatAttribute("y", &y);

        if (!strcmp(rect->Attribute("fill"), "blue")) {
            data->arena_depth = height/2.f;
            data->arena_height = height;
            data->arena_width = width;
        } else {
            tmp.push_back({
                .width = width,
                .height = height,
                .x = x, .y = y });
        }
    }

    std::vector<std::shared_ptr<Box>> rects;

    normalize_centers();
    create_boxes(&tmp, &rects, data);

    data->rects = rects;
}

std::shared_ptr<SVGReader> readSVG(const char* file_path) {
    std::shared_ptr<SVGReader> data = std::make_shared<SVGReader>();
    XMLDocument svg;

    XMLError err = svg.LoadFile(file_path);
    if (err != XML_SUCCESS) std::cout << "Insira um arquivo existente";

    get_rects(data, &svg);

    return data;
}
