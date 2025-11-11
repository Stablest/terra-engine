#include "renderer_texture_2d.hpp"
#include "terra_opengl.hpp"

RendererTexture2D::RendererTexture2D(const unsigned char *data, const Size width, const Size height,
                                     const int channels) {
    TextureId id;
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

RendererTexture2D::RendererTexture2D(const TextureResource& resource)
    : RendererTexture2D(resource.getBuffer().data(), resource.getWidth(), resource.getHeight(),
                        resource.getChannels()) {
}

void RendererTexture2D::bind() const {
    glBindTexture(GL_TEXTURE_2D, id_);
}

TextureId RendererTexture2D::getId() const {
    return id_;
}

int RendererTexture2D::getWidth() const {
    return width_;
}

int RendererTexture2D::getHeight() const {
    return height_;
}

