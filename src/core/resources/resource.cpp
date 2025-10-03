#include "resource.hpp"

#include <filesystem>

const std::string &Resource::getPath() const {
    return path_;
}

const std::vector<std::byte> &Resource::getBuffer() const {
    return buffer_;
}

const unsigned char *Resource::getAsChar() {
    return reinterpret_cast<unsigned char *>(buffer_.data());
}

TextureResource::TextureResource(const int width, const int height, const int channels,
                                 std::string path, std::vector<std::byte> buffer) : Resource(std::move(path),
        std::move(buffer)),
    _width(width), _height(height), _channels(channels) {
}

int TextureResource::getWidth() const {
    return _width;
}

int TextureResource::getHeight() const {
    return _height;
}

int TextureResource::getChannels() const {
    return _channels;
}

ShaderResource::ShaderResource(std::string path, std::vector<std::byte> _buffer)
    : Resource(std::move(path), std::move(_buffer)) {
}
