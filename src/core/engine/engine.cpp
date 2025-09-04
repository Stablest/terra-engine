#include "engine.hpp"
#include "terra-opengl.hpp"

void Engine::startLoop() const {
    while (!window.shouldClose()) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwPollEvents();
        window.swapBuffers();
    }
}

Engine::Engine(const int width, const int height, const char *title) : window(width, height, title) {
    startLoop();
}

