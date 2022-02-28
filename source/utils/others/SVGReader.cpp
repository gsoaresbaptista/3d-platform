#include "SVGReader.h"
#include "../linear/vec3.h"
#include <iostream>
#include <string.h>

typedef struct {
    float width;
    float height;
    float x;
    float y;
} Object;

static void normalize_centers(
        std::vector<Object>* tmp,
        std::shared_ptr<SVGReader> data) {
    for (auto& shape : *tmp) {
        shape.x = shape.x - data->arena_x + shape.width/2.f;
        shape.y = data->arena_height - shape.y +
                  data->arena_y - shape.height/2.f;
    }
}

static void create_boxes(
        std::vector<Object>* tmp,
        std::vector<std::shared_ptr<Box>>* rects,
        std::shared_ptr<SVGReader> data) {
    for (auto& rect : *tmp) {
        BoxType type = BoxType::WOOD;
        vec3 center = vec3(rect.x, rect.y, data->arena_depth/2.f);

        if (center.y - rect.height <= 0) {
            type = BoxType::STONE;
        }

        rects->push_back(std::make_shared<Box>(
            center, rect.width, rect.height, data->arena_depth, type));
    }
}

static void get_rects(std::shared_ptr<SVGReader> data, XMLDocument* svg) {
    vector<Object> tmp;
    XMLElement* file = svg->FirstChildElement();
    XMLElement* rect = file->FirstChildElement("rect");
    std::vector<std::shared_ptr<Box>> rects;

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
            data->arena_x = x;
            data->arena_y = y;
        } else {
            tmp.push_back({
                .width = width,
                .height = height,
                .x = x, .y = y });
        }
    }

    normalize_centers(&tmp, data);
    create_boxes(&tmp, &rects, data);

    data->rects = rects;
}

static void get_circles(std::shared_ptr<SVGReader> data, XMLDocument* svg) {
    vector<Object> tmp;
    XMLElement* file = svg->FirstChildElement();
    XMLElement* circ = file->FirstChildElement("circle");
    // std::vector<std::shared_ptr<Box>> rects;

    for (; circ != NULL; circ = circ->NextSiblingElement("circle")) {
        float radius, cx, cy;

        circ->QueryFloatAttribute("cx", &cx);
        circ->QueryFloatAttribute("cy", &cy);
        circ->QueryFloatAttribute("r", &radius);

        if (!strcmp(circ->Attribute("fill"), "green")) {
            data->block_size = radius;
        } else {
        }
    }
}

std::shared_ptr<SVGReader> readSVG(const char* file_path) {
    std::shared_ptr<SVGReader> data = std::make_shared<SVGReader>();
    XMLDocument svg;

    XMLError err = svg.LoadFile(file_path);
    if (err != XML_SUCCESS) std::cout << "Insira um arquivo existente";

    get_rects(data, &svg);
    get_circles(data, &svg);

    return data;
}
