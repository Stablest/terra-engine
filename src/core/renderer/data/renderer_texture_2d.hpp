#pragma once
#include "core/resources/texture/texture_resource.hpp"

using TextureId = unsigned int;

using Size = int;

class RendererTexture2D {
    TextureId id_ = 0;
    int width_ = 0, height_ = 0;

public:
    RendererTexture2D() = default;

    explicit RendererTexture2D(const unsigned char *data, Size width, Size height, int channels);

    explicit RendererTexture2D(const TextureResource &resource);

    inline void bind() const;

    [[nodiscard]] TextureId getId() const;

    [[nodiscard]] int getWidth() const;

    [[nodiscard]] int getHeight() const;
};
