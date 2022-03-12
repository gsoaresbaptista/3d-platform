#include <vector>
#include <iostream>
#include <memory>
#include "objReader.h"

vec3 ObjReader::get_vertice(std::string text) {
    float x, y, z;
    sscanf(text.c_str(), "v %f %f %f", &x, &y, &z);
    return vec3(x, y, z);
}

face ObjReader::get_face(std::string text) {
    int v1, v2, v3, n1, n2, n3, t1, t2, t3;

    sscanf(text.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d",
            &v1, &t1, &n1, &v2, &t2, &n2, &v3, &t3, &n3);

    return face(v1, v2, v3, n1, n2, n3, t1, t2, t3);
}

vec3 ObjReader::get_normal(std::string text) {
    float x, y, z;
    sscanf(text.c_str(), "vn %f %f %f", &x, &y, &z);
    return vec3(x, y, z);
}

vec2 ObjReader::get_texture(std::string text) {
    float s, t;
    sscanf(text.c_str(), "vt %f %f", &s, &t);
    return vec2(s, t);
}

void ObjReader::load_obj(
        GLuint* id,
        const char* file_path,
        std::shared_ptr<Texture> texture) {
    //
    std::vector<vec3> vertices;
    std::vector<vec3> normals;
    std::vector<vec2> textures;
    std::vector<face> faces;

    std::fstream file(file_path);
    std::string line = "";

    if (!file.is_open()) {
        std::cout << "ERROR: Could not open file: "
                  << file_path << "!" << std::endl;
    }

    while (getline(file, line)) {
        if (line.find("v ") != std::string::npos) {
            vertices.push_back(ObjReader::get_vertice(line));

        } else if (line.find("vn ") != std::string::npos) {
            normals.push_back(ObjReader::get_normal(line));

        } else if (line.find("vt ") != std::string::npos) {
            textures.push_back(ObjReader::get_texture(line));

        } else if (line.find("f ") != std::string::npos) {
            faces.push_back(ObjReader::get_face(line));
        }
    }

    *id = glGenLists(1);
    glNewList(*id, GL_COMPILE);
        if (texture != nullptr) texture->bind();
        glPolygonMode(GL_FRONT, GL_FILL);
        for (int i = 0; i < faces.size(); i++) {
            int v1 = faces[i].vertice[0] - 1;
            int v2 = faces[i].vertice[1] - 1;
            int v3 = faces[i].vertice[2] - 1;
            //
            int n1 = faces[i].normal[0] - 1;
            int n2 = faces[i].normal[1] - 1;
            int n3 = faces[i].normal[2] - 1;
            //
            int t1 = faces[i].texture[0] - 1;
            int t2 = faces[i].texture[1] - 1;
            int t3 = faces[i].texture[2] - 1;

            glBegin(GL_TRIANGLES);
                glTexCoord2fv(&textures[t1].x);
                glNormal3fv(&normals[n1].x), glVertex3fv(&vertices[v1].x);
                glTexCoord2fv(&textures[t2].x);
                glNormal3fv(&normals[n2].x), glVertex3fv(&vertices[v2].x);
                glTexCoord2fv(&textures[t3].x);
                glNormal3fv(&normals[n3].x), glVertex3fv(&vertices[v3].x);
            glEnd();
        }
    if (texture != nullptr) texture->unbind();
    glEndList();
}
