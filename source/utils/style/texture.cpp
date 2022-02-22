#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include "../libs/stb_image.h"
#include "texture.h"

Texture::Texture() {
    this->id = 0;
    this->width = 0;
    this->height = 0;
    this->channels = 0;
}

std::shared_ptr<Texture> Texture::load(std::string file_path, bool mipmap) {
    //
    auto texture = std::make_shared<Texture>();

    stbi_set_flip_vertically_on_load(true);

    unsigned char* img_data = stbi_load(
        file_path.c_str(), &texture->width, &texture->height,
        &texture->channels, STBI_rgb_alpha);

    if (img_data) {
        glGenTextures(1, &texture->id);
        glBindTexture(GL_TEXTURE_2D, texture->id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        if (mipmap) {
            gluBuild2DMipmaps(
                GL_TEXTURE_2D, GL_RGBA, texture->width, texture->height,
                GL_RGBA, GL_UNSIGNED_BYTE, img_data);
            glTexParameteri(
                GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                GL_LINEAR_MIPMAP_LINEAR);
        } else {
            glTexImage2D(
                GL_TEXTURE_2D, 0, GL_RGBA, texture->width, texture->height, 0,
                GL_RGBA, GL_UNSIGNED_BYTE, img_data);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        }

        glBindTexture(GL_TEXTURE_2D, 0);
        stbi_image_free(img_data);
    } else {
        std::cout << "ERROR: Failed to load file: " << file_path << std::endl;
        return nullptr;
    }

    return texture;
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, this->id);
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture() {
    glDeleteTextures(1, &this->id);
}
