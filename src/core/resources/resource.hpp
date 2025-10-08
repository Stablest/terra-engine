#pragma once
#include <filesystem>
#include <string>
#include <vector>

class Resource {
    std::filesystem::path path_;
public:
    explicit Resource(std::filesystem::path path) : path_(std::move(path)) {
    }

    [[nodiscard]] const std::filesystem::path &getPath() const;
};

class TextureResource : public Resource {
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

class ShaderResource : public Resource {
    std::string data_;
public:
    explicit ShaderResource(std::filesystem::path path, std::string data);
};
