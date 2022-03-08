#ifndef SOURCE_UTILS_OTHERS_OBJREADER_H_
#define SOURCE_UTILS_OTHERS_OBJREADER_H_

#include <GL/gl.h>
#include <string>
#include <fstream>
#include <sstream>
#include <memory>
#include "../math/math.h"
#include "../style/texture.h"

struct face {
    GLint vertice[3];
    GLint normal[3];
    GLint texture[3];

    face(
        GLint v1, GLint v2, GLint v3,
        GLint n1, GLint n2, GLint n3,
        GLfloat t1, GLfloat t2, GLfloat t3) {
        //
        vertice[0] = v1, vertice[1] = v2, vertice[2] = v3;
        normal[0] = n1, normal[1] = n2, normal[2] = n3;
        texture[0] = t1, texture[1] = t2, texture[2] = t3;
    }
};

namespace ObjReader{
    vec3 get_vertice(std::string text);
    vec3 get_normal(std::string text);
    vec2 get_texture(std::string text);
    face get_face(std::string text);
    void load_obj(
        GLuint* id,
        const char* file_path,
        std::shared_ptr<Texture> texture);
};

#endif  // SOURCE_UTILS_OTHERS_OBJREADER_H_
