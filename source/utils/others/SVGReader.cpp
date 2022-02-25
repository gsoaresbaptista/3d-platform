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

static void get_rects(SVGReader* data, XMLDocument* svg) {
    vector<Rect> tmp;
    XMLElement* file = svg->FirstChildElement();

    for (XMLElement* rect = file->FirstChildElement("rect"); rect != NULL; rect = rect->NextSiblingElement("rect")) {
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
            Rect newRect = { .width = width, .height = height, .x = x, .y = y };
            tmp.push_back(newRect);
        }
    }

    std::vector<std::shared_ptr<Box>> rects;

    for (auto& rect : tmp) {
        vec3 center = vec3(rect.x, rect.y, data->arena_depth/2.f);
        // rects.push_back(Box(
            // vec3(rect.x, rect.y, data->arena_depth/2.f),
            // rect.width, rect.height, data->arena_depth));
        rects.push_back(std::make_shared<Box>(center, rect.width, rect.height, data->arena_depth));
    }

    data->rects = rects;
}

SVGReader* readSVG(const char* file_path) {
    XMLDocument svg;
    SVGReader* data = new SVGReader();

    XMLError err = svg.LoadFile(file_path);
    if (err != XML_SUCCESS) std::cout << "Insira um arquivo existente";


    get_rects(data, &svg);

    return data;
}
