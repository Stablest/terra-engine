#pragma once

using TextureID = unsigned int;

class Texture2D {
    TextureID id_ = 0;
    unsigned int width_ = 0, height_ = 0;
    unsigned int imageFormat_ = 0;
public:
    unsigned int wrapS_ = 0, wrapT_ = 0;
    unsigned int filterMin_ = 0, filterMax_ = 0;
    explicit Texture2D(const unsigned char* data);

    inline void bind() const;

    [[nodiscard]] TextureID getID() const;
};
