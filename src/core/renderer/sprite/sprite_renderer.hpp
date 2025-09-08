#pragma once
#include "sprite_render_queue.hpp"
#include "core/shader/shader_program.hpp"
#include "glm/ext/matrix_float4x4.hpp"

struct Transform;
struct Sprite;

class SpriteRenderer {
    ShaderProgram fallbackShader_;
    SpriteRenderQueue renderQueue_;
    GLuint quadVAO_ = 0;
    GLuint quadVBO_ = 0;
    GLuint currentTexture_;
    glm::mat4 projection_;

public:
    SpriteRenderer();

    void render();

    void queueDraw(const SpriteDrawCommand& drawCommand);
};
