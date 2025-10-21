#include "texture_resource.hpp"

TextureResource::TextureResource(const int width, const int height, const int channels,
                                 std::filesystem::path path,
                                 std::vector<unsigned char> buffer) : Class(std::move(path)),
                                                                      width_(width), height_(height),
                                                                      channels_(channels), buffer_(std::move(buffer)) {
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

const std::vector<unsigned char> &TextureResource::getBuffer() const {
    return buffer_;
}
