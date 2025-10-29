#pragma once
#include <vector>
#include "core/math/matrix4.hpp"
#include "core/renderer/data/renderer_texture_2d.hpp"

struct SpriteDrawCommand {
    TextureId texture_ = 0;
    int renderLayer_ = 0;
    Matrix4 model_ = Matrix4(1.0f);
    mutable unsigned int sortKey_ = 0;
};

class SpriteRenderQueue {
    std::vector<SpriteDrawCommand> commands_;
public:
    void submit(const SpriteDrawCommand& command);
    void clear();
    void sort();
    [[nodiscard]] const std::vector<SpriteDrawCommand>& getCommands() const;
};
