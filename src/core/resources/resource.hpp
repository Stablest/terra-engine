#pragma once
#include <string>
#include <vector>

class Resource {
    std::string path_;
public:
    explicit Resource(std::string path) : path_(std::move(path)) {
    }

    [[nodiscard]] const std::string &getPath() const;
};

class TextureResource : public Resource {
    int width_ = 0, height_ = 0, channels_ = 0;
    std::vector<unsigned char> buffer_;

public:
    TextureResource(int width, int height, int channels, std::string path,
                    std::vector<unsigned char> buffer);

    [[nodiscard]] int getWidth() const;

    [[nodiscard]] int getHeight() const;

    [[nodiscard]] int getChannels() const;

    [[nodiscard]] const std::vector<unsigned char> &getBuffer() const;

};

class ShaderResource : public Resource {
    std::string data_;
public:
    explicit ShaderResource(std::string path, std::string data);
};
