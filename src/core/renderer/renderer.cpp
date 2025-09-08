#include "renderer.hpp"
#include "render_queue.hpp"

void Renderer::render(RenderQueue& queue) {
    queue.sort();
    GLuint currentShader = 0;
    GLuint currentTexture = 0;
    for (const auto& command: queue.getCommands()) {
        if (command.shader_ != currentShader) {
            currentShader = command.shader_;
            if (currentShader != 0) {
                glUseProgram(currentShader);
            }
        }
        if (command.texture_ != currentTexture) {
            currentTexture = command.texture_;
            if (currentTexture != 0) {
                glBindTexture(GL_TEXTURE0, command.texture_);
            }
        }
        glBindVertexArray(command.vao_);
        glDrawElements(command.drawMode_, command.vertexCount_, GL_UNSIGNED_INT, nullptr);
    }
}

