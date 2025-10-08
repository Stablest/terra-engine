#include "resource.hpp"
#include <filesystem>

const std::filesystem::path &Resource::getPath() const {
    return path_;
}

TextureResource::TextureResource(const int width, const int height, const int channels,
                                 std::filesystem::path path, std::vector<unsigned char> buffer) : Resource(std::move(path)),
    width_(width), height_(height), channels_(channels), buffer_(std::move(buffer)) {
}

int TextureResource::getWidth() const {
    return width_;
}

int TextureResource::getHeight() const {
    return height_;
}

int TextureResource::getChannels() const {
    return channels_;
}

const std::vector<unsigned char> & TextureResource::getBuffer() const {
    return buffer_;
}

ShaderResource::ShaderResource(std::filesystem::path path, std::string data)
    : Resource(std::move(path)), data_(std::move(data)) {
}
