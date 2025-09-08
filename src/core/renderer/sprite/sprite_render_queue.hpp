#pragma once
#include <vector>

#include "glad/glad.h"
#include "glm/ext/matrix_float4x4.hpp"

struct SpriteDrawCommand {
    GLuint texture_ = 0;
    int renderLayer_ = 0;
    glm::mat4 model_ = glm::mat4(1.0f);
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
