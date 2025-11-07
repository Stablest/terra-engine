#include "engine.hpp"
#include <iostream>
#include "game.hpp"
#include "terra_opengl.hpp"
#include "core/ecs/component/component_manager.hpp"
#include "core/resources/resource_loader.hpp"
#include "core/resources/resource_manager.hpp"
#include "core/resources/shader/shader_loader.hpp"
#include "core/resources/texture/texture_loader.hpp"
#include "glm/ext/matrix_transform.hpp"

void Engine::startLoop() {
    while (!window_.shouldClose()) {
        glfwPollEvents();
        game_->update();
        queueSprites();
        renderer_.render();
        window_.swapBuffers();
    }
}

void Engine::queueSprites() {
    ComponentSignature spriteSignature;
    spriteSignature.set(getComponentType<Transform>());
    spriteSignature.set(getComponentType<Sprite>());
    const auto renderedEntities = EntityManager::getInstance().getEntitiesWithSignature(spriteSignature);
    for (const Entity entity: renderedEntities) {
        auto &[position, rotation, scale] = ComponentManager::getInstance().getComponent<Transform>(entity);
        auto &sprite = ComponentManager::getInstance().getComponent<Sprite>(entity);
        auto model = Matrix4(1.0f);
        model = glm::translate(model, position);
        model = glm::rotate(model, rotation, Vector3(0, 0, 1));
        model = glm::scale(model, Vector3{sprite.rect.size.x * scale.x, sprite.rect.size.y * scale.y, 1});
        renderer_.queueSprite({sprite.texture->getID(), sprite.rect, 0, model, 0});
    }
}

Engine::Engine(const int width, const int height, const char *title, IGame *game) : window_(width, height, title),
    game_(game) {
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    registerDefaultComponents();
    registerResourceLoaders();
    game_->create();
    startLoop();
}

void Engine::registerDefaultComponents() {
    ComponentManager::getInstance().registerComponent<Transform>();
    ComponentManager::getInstance().registerComponent<Sprite>();
}

void Engine::registerResourceLoaders() {
    ResourceManager::getInstance().addLoader(std::make_unique<ImageLoader>());
    ResourceManager::getInstance().addLoader(std::make_unique<ShaderLoader>());
}
