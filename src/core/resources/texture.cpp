#include "texture.hpp"
#include "glad/glad.h"

Texture2D::Texture2D(const unsigned char *data, const GLsizei width, const GLsizei height, const int channels) {
    TextureID id;
    glGenTextures(1, &id);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, id);
    // TODO As parameter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //
    const GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;
    const GLenum internalFormat = (channels == 4) ? GL_RGBA8 : GL_RGB8;
    glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLint>(internalFormat), width, height, 0, format,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    this->id_ = id;
    this->width_ = width;
    this->height_ = height;
}

void Texture2D::bind() const {
    glBindTexture(GL_TEXTURE_2D, id_);
}

TextureID Texture2D::getID() const {
    return id_;
}
