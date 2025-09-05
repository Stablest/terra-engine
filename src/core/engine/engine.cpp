#include "engine.hpp"
#include "terra_opengl.hpp"
#include "core/shader/resources/default_shaders.h"

void Engine::startLoop() const {
    while (!window_.shouldClose()) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwPollEvents();
        window_.swapBuffers();
    }
}

Engine::Engine(const int width, const int height, const char *title) : window_(width, height, title),
                                                                       shaderProgram_(
                                                                           ShaderProgram::createDefaultProgram(
                                                                               ShaderProgram::createDefaultShader(
                                                                                   GL_VERTEX_SHADER,
                                                                                   default_vertex_shader
                                                                               ),
                                                                               ShaderProgram::createDefaultShader(
                                                                                   GL_FRAGMENT_SHADER,
                                                                                   default_frag_shader))
                                                                       ) {
    startLoop();
}
