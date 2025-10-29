#pragma once
#include "sprite_render_queue.hpp"
#include "core/renderer/data/renderer_texture_2d.hpp"
#include "core/shader/shader_program.hpp"

struct Transform;
struct Sprite;

class SpriteRenderer {
    ShaderProgram fallbackShader_;
    SpriteRenderQueue renderQueue_;
    unsigned int quadVAO_ = 0;
    unsigned int quadVBO_ = 0;
    TextureId currentTexture_;
    Matrix4 projection_;

public:
    SpriteRenderer();

    void render();

    void queueDraw(const SpriteDrawCommand& drawCommand);
};
