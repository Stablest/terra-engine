#include "engine.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

void Engine::start_loop() const {
    while (!window.shouldClose()) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwPollEvents();
        window.swapBuffers();
    }
}

Engine::Engine(const int width, const int height, const char *title) : window(width, height, title) {
    start_loop();
}

Engine::~Engine() = default;

