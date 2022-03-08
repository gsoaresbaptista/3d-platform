#include "material.h"
#include <GL/gl.h>

Material::Material(
        float amb_r, float amb_g, float amb_b,
        float diff_r, float diff_g, float diff_b,
        float spec_r, float spec_g, float spec_b,
        float _shininess, float emiss_r,
        float emiss_g, float emiss_b) {
    ambient[0] = amb_r, ambient[1] = amb_g,
    ambient[2] = amb_b, ambient[3] = 1.0f;
    //
    diffuse[0] = diff_r, diffuse[1] = diff_g,
    diffuse[2] = diff_b, diffuse[3] = 1.0f;
    //
    specular[0] = spec_r, specular[1] = spec_g,
    specular[2] = spec_b, specular[3] = 1.0f;
    //
    emission[0] = emiss_r, emission[1] = emiss_g,
    emission[2] = emiss_b;
    //
    shininess = _shininess * 128;
}

Material::~Material() {
}

void Material::activate() {
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_EMISSION, emission);
    glMaterialf(GL_FRONT, GL_SHININESS, 128*shininess);
}
