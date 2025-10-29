#pragma once
#include "core/resources/texture/texture_resource.hpp"
#include "glad/glad.h"

using TextureId = unsigned int;

using Size = int;

class RendererTexture2D {
    TextureId id_ = 0;
    unsigned int width_ = 0, height_ = 0;

public:
    unsigned int wrapS_ = 0, wrapT_ = 0;
    unsigned int filterMin_ = 0, filterMax_ = 0;

    explicit RendererTexture2D(const unsigned char *data, Size width, Size height, int channels);

    explicit RendererTexture2D(const TextureResource &resource);

    inline void bind() const;

    [[nodiscard]] TextureId getID() const;
};
