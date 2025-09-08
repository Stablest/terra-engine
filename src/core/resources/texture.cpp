#include "texture.hpp"

#include <iostream>

#include "glad/glad.h"

Texture2D::Texture2D(const unsigned char *data) {
    TextureID id;
    constexpr int width = 0;
    constexpr int height = 0;
    glGenTextures(1, &id);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, id);
    // TODO As parameter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 32, 32, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    this->id_ = id;
    this->width_ = 32;
    this->height_ = 32;
}

void Texture2D::bind() const {
    glBindTexture(GL_TEXTURE_2D, id_);
}

TextureID Texture2D::getID() const {
    return id_;
}
