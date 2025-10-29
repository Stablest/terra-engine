#include "sprite_renderer.hpp"
#include "core/ecs/entity-manager.hpp"
#include "core/shader/resources/default_shaders.h"
#include "glm/gtc/type_ptr.hpp"

static void createQuadVAO(const unsigned int quadVAO, const unsigned int quadVBO) {
    constexpr float vertices[] = {
        -0.5f, -0.5f, 0.0f, 0.0f, // bottom-left
        0.5f, -0.5f, 1.0f, 0.0f, // bottom-right
        0.5f, 0.5f, 1.0f, 1.0f, // top-right

        0.5f, 0.5f, 1.0f, 1.0f, // top-right
        -0.5f, 0.5f, 0.0f, 1.0f, // top-left
        -0.5f, -0.5f, 0.0f, 0.0f // bottom-left
    };
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), static_cast<void *>(nullptr));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), reinterpret_cast<void *>(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

SpriteRenderer::SpriteRenderer() : fallbackShader_(
                                       ShaderProgram::createDefaultProgram(
                                           ShaderProgram::compileDefaultShader(
                                               GL_VERTEX_SHADER,
                                               default_vertex_shader
                                           ),
                                           ShaderProgram::compileDefaultShader(
                                               GL_FRAGMENT_SHADER,
                                               default_frag_shader
                                           )
                                           , 0)),
                                   currentTexture_(0),
                                   projection_(glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f)) {
    glGenBuffers(1, &quadVBO_);
    glGenVertexArrays(1, &quadVAO_);
    createQuadVAO(quadVAO_, quadVBO_);
}

void SpriteRenderer::render() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    renderQueue_.sort();
    for (const auto &command: renderQueue_.getCommands()) {
        fallbackShader_.use();
        if (command.texture_ != currentTexture_) {
            currentTexture_ = command.texture_;
            if (currentTexture_ != 0) {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, currentTexture_);
                fallbackShader_.setInt("texture0", 0);
            }
        }
        fallbackShader_.setMatrix4("projection", glm::value_ptr(projection_));
        fallbackShader_.setMatrix4("model", glm::value_ptr(command.model_));
        glBindVertexArray(quadVAO_);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
    renderQueue_.clear();
}

void SpriteRenderer::queueDraw(const SpriteDrawCommand &drawCommand) {
    renderQueue_.submit(drawCommand);
}
