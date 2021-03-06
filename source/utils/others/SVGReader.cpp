#include "SVGReader.h"
#include "../math/math.h"
#include "../gameShapes/chain.h"
#include "../gameShapes/plane.h"
#include "../gameShapes/animatedPlane.h"
#include <iostream>
#include <string.h>

struct Object {
    float width;
    float height;
    float x;
    float y;

    bool operator==(const Object& obj) {
        return (width == obj.width) && (height == obj.height) &&
               (x == obj.x) && (y == obj.y);
    }

    bool operator!=(const Object& obj) {
        return !(*this == obj);
    }

    bool collision(const Object& obj) {
        return distance(x, obj.x) <= width/2 + obj.width/2 &&
               distance(y, obj.y) <= height/2 + obj.height/2;
    }
};

struct CircleObject {
    float cx;
    float cy;
    float radius;
};

static void normalize_centers(
        std::vector<Object>* tmp,
        std::shared_ptr<SVGData> data) {
    for (auto& shape : *tmp) {
        shape.x = shape.x - data->arena_x + shape.width/2.f;
        shape.y = data->arena_height - shape.y +
                  data->arena_y - shape.height/2.f;
    }
}

static void normalize_center(
        CircleObject* obj,
        std::shared_ptr<SVGData> data) {
    obj->cx = obj->cx - data->arena_x;
    obj->cy = data->arena_height - obj->cy + data->arena_y;
}

static void normalize_centers(
        std::vector<CircleObject>* tmp,
        std::shared_ptr<SVGData> data) {
    for (auto& shape : *tmp) {
        normalize_center(&shape, data);
    }
}

static void create_boxes(
        std::vector<Object>* tmp,
        std::vector<std::shared_ptr<Shape>>* rects,
        std::shared_ptr<SVGData> data) {
    //
    bool collided = false;

    for (auto& rect : *tmp) {
        collided = false;
        BoxType type = BoxType::SPRUCE;
        vec3 center = vec3(rect.x, rect.y, data->arena_depth/2.f);

        for (auto& rect0 : *tmp) {
            if ((rect != rect0) && rect.collision(rect0)) {
                collided = true;
            }
        }

        if ((center.y - rect.height <= 0) || collided) {
            type = BoxType::DEEPSLATE_BRICKS;
        }

        float depth = data->arena_depth;

        if (type == BoxType::SPRUCE) {
            depth *= 0.60;

            for (int i = 0; i < 4; i++) {
                // Create chains
                float cheight = data->arena_height - rect.y;
                float cwidth = data->arena_depth * 0.025;

                int fconst = (i <= 1) ? -1:1;

                float center_x = rect.x + fconst*(rect.width/2 - 1.5*cwidth);
                float center_z = data->arena_depth - 1.25*cwidth;

                if (i % 2 == 0)
                    center_z *= 0.75;
                else
                    center_z *= 0.25;

                Object chain = {
                    .width = cwidth, .height = cheight,
                    .x = center_x, .y = rect.y + cheight/2};

                for (auto& rect0 : *tmp) {
                    if ((rect0 != rect) && chain.collision(rect0)) {
                        cheight -= data->arena_height - rect0.y;
                    }
                }

                vec3 ccenter(center_x, rect.y + cheight/2, center_z);
                rects->push_back(std::make_shared<Chain>(
                    ccenter, cwidth, cheight, cwidth));
            }
        }

        rects->push_back(std::make_shared<Box>(
            center, rect.width, rect.height, depth, type));
    }
}

static void add_torchs(std::shared_ptr<SVGData> data) {
    float space = data->arena_width/8.0;
    float height = data->arena_height;

    for (int i = 0; i < 7; i++) {
        glEnable(GL_LIGHT0 + i);
        vec3 center((i + 1)*space,
            data->arena_height/2.f, 1.1*data->block_size);
        data->rects.push_back(std::make_shared<Torch>(center));
        data->torchs.push_back(std::make_shared<Torch>(center));
    }

    //
    glEnable(GL_LIGHT7);
}

static void get_rects(std::shared_ptr<SVGData> data, XMLDocument* svg) {
    vector<Object> tmp;
    XMLElement* file = svg->FirstChildElement();
    XMLElement* rect = file->FirstChildElement("rect");
    std::vector<std::shared_ptr<Shape>> rects;

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

static void create_enemies(
        vector<CircleObject>* tmp, std::shared_ptr<SVGData> data) {
    //
    for (auto& enemy : *tmp) {
        data->enemies.push_back(std::make_shared<Enemy>(
            vec3(enemy.cx, enemy.cy, data->arena_depth/2.f), enemy.radius));
    }
}

static void get_circles(std::shared_ptr<SVGData> data, XMLDocument* svg) {
    vector<CircleObject> tmp;
    XMLElement* file = svg->FirstChildElement();
    XMLElement* circ = file->FirstChildElement("circle");

    for (; circ != NULL; circ = circ->NextSiblingElement("circle")) {
        float radius, cx, cy;

        circ->QueryFloatAttribute("cx", &cx);
        circ->QueryFloatAttribute("cy", &cy);
        circ->QueryFloatAttribute("r", &radius);

        if (!strcmp(circ->Attribute("fill"), "green")) {
            CircleObject player = { .cx = cx, .cy = cy, .radius = radius };
            normalize_center(&player, data);
            data->block_size = radius;
            data->player_pos = vec3(
                player.cx, player.cy, data->arena_depth/2.0);
        } else {
            CircleObject new_enemy = { .cx = cx, .cy = cy, .radius = radius };
            tmp.push_back(new_enemy);
        }
    }

    normalize_centers(&tmp, data);
    create_enemies(&tmp, data);
}

static void add_bounds(std::shared_ptr<SVGData> data) {
    // Left
    vec3 b0(0, data->arena_height, 0);
    vec3 b1(0, 0, 0);
    vec3 b2(0, 0, data->arena_depth);
    vec3 b3(0, data->arena_height, data->arena_depth);

    // Right
    vec3 b4(data->arena_width, data->arena_height, 0);
    vec3 b5(data->arena_width, 0, 0);
    vec3 b6(data->arena_width, 0, data->arena_depth);
    vec3 b7(data->arena_width, data->arena_height, data->arena_depth);

    data->rects.push_back(std::make_shared<Plane>(
        b6, b5, b1, b2, vec3(0, 1, 0), BoxType::DARK_OAK,
        vec3(data->arena_width/2.f, 0, data->arena_depth/2.f)));  // Floor

    data->rects.push_back(std::make_shared<Plane>(
        b3, b0, b4, b7, vec3(0, -1, 0), BoxType::DARK_OAK,
        vec3(data->arena_width/2.f, data->arena_height, data->arena_depth/2.f)));  // Roof

    data->rects.push_back(std::make_shared<Plane>(
        b3, b2, b1, b0, vec3(1, 0, 0), BoxType::DEEPSLATE_BRICKS,
        vec3(0.1, data->arena_height/2.f, data->arena_depth/2.f)));  // Wall left

    data->rects.push_back(std::make_shared<AnimatedPlane>(
        b4, b5, b6, b7, vec3(0, -1, 0),
        vec3(data->arena_width, data->arena_height/2.f, data->arena_depth/2.f),
        PORTAL_TEX, 32));  // Portal / Wall Right

    data->rects.push_back(std::make_shared<Plane>(
        b7, b6, b2, b3, vec3(0, 0, -1), BoxType::DEEPSLATE_BRICKS,
        vec3(data->arena_width/2.f, data->arena_height/2.f, data->arena_depth)));  // Wall Back

    data->rects.push_back(std::make_shared<Plane>(
        b0, b1, b5, b4, vec3(0, 0, 1), BoxType::DEEPSLATE_BRICKS,
        vec3(data->arena_width/2.f, data->arena_height/2.f, 0)));  // Wall Front
}

std::shared_ptr<SVGData> readSVG(const char* file_path) {
    std::shared_ptr<SVGData> data = std::make_shared<SVGData>();
    XMLDocument svg;

    XMLError err = svg.LoadFile(file_path);
    if (err != XML_SUCCESS) {
        std::cout << "Insira um arquivo existente\n";
        exit(EXIT_SUCCESS);
    } 

    get_rects(data, &svg);
    get_circles(data, &svg);
    add_bounds(data);
    add_torchs(data);

    return data;
}
