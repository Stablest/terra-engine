#include "renderer.hpp"

void Renderer::render() {
    spriteRenderer_.render();
}

void Renderer::queueSprite(const SpriteDrawCommand& drawCommand) {
    spriteRenderer_.queueDraw(drawCommand);
}
