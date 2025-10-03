#include "renderer_texture_2d.hpp"
#include "glad/glad.h"

RendererTexture2D::RendererTexture2D(const unsigned char *data, const GLsizei width, const GLsizei height,
                                     const int channels) {
    TextureID id;
    glGenTextures(1, &id);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, id);
    // TODO As parameter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //
    const GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;
    const GLenum internalFormat = (channels == 4) ? GL_RGBA8 : GL_RGB8;
    glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLint>(internalFormat), width, height, 0, format,
                 GL_UNSIGNED_BYTE, data);
    this->id_ = id;
    this->width_ = width;
    this->height_ = height;
}

RendererTexture2D::RendererTexture2D(const std::unique_ptr<TextureResource> &resource)
    : RendererTexture2D(resource->getAsChar(), resource->getWidth(), resource->getHeight(), resource->getChannels()) {
}

void RendererTexture2D::bind() const {
    glBindTexture(GL_TEXTURE_2D, id_);
}

TextureID RendererTexture2D::getID() const {
    return id_;
}
