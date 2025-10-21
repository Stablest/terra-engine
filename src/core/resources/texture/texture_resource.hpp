#pragma once
#include <filesystem>
#include <vector>
#include "core/resources/resource.hpp"

class TextureResource final : public Class<TextureResource, Resource> {
    int width_ = 0, height_ = 0, channels_ = 0;
    std::vector<unsigned char> buffer_;

public:
    TextureResource(int width, int height, int channels, std::filesystem::path path,
                    std::vector<unsigned char> buffer);

    [[nodiscard]] int getWidth() const;

    [[nodiscard]] int getHeight() const;

    [[nodiscard]] int getChannels() const;

    [[nodiscard]] const std::vector<unsigned char> &getBuffer() const;
};
