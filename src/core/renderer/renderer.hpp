#pragma once
#include "sprite/sprite_renderer.hpp"

class Renderer {
    SpriteRenderer spriteRenderer_;
    public:
    void render();

    void queueSprite(const SpriteDrawCommand& drawCommand);
};
