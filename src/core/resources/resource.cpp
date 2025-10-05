#include "resource.hpp"
#include <filesystem>

const std::string &Resource::getPath() const {
    return path_;
}

TextureResource::TextureResource(const int width, const int height, const int channels,
                                 std::string path, std::vector<unsigned char> buffer) : Resource(std::move(path)),
    _width(width), _height(height), _channels(channels), _buffer(std::move(buffer)) {
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

const std::vector<unsigned char> & TextureResource::getBuffer() const {
    return _buffer;
}

ShaderResource::ShaderResource(std::string path, std::string data)
    : Resource(std::move(path)), _data(std::move(data)) {
}
