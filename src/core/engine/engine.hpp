#pragma once

#include "../window/window.hpp"
#include "core/shader/shader_program.hpp"

class Engine {
    Window window;
    ShaderProgram shaderProgram_;

    void startLoop() const;

public:
    Engine(int width, int height, const char *title);
};
