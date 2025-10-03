#pragma once
#include <string>
#include <vector>

class Resource {
    std::string path_;
    std::vector<std::byte> buffer_;

public:
    explicit Resource(std::string path, std::vector<std::byte> buffer) : path_(std::move(path)),
                                                                         buffer_(std::move(buffer)) {
    }

    [[nodiscard]] const std::string &getPath() const;

    [[nodiscard]] const std::vector<std::byte> &getBuffer() const;

    [[nodiscard]] const unsigned char *getAsChar();
};

class TextureResource : public Resource {
    int _width = 0, _height = 0, _channels = 0;

public:
    TextureResource(int width, int height, int channels, std::string path,
                    std::vector<std::byte> buffer);

    [[nodiscard]] int getWidth() const;

    [[nodiscard]] int getHeight() const;

    [[nodiscard]] int getChannels() const;
};

class ShaderResource : public Resource {
public:
    explicit ShaderResource(std::string path, std::vector<std::byte> _buffer);
};
