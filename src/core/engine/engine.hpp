#pragma once

#include "../window/window.hpp"
#include "core/shader/shader_program.hpp"

class Engine {
    Window window_;
    ShaderProgram shaderProgram_;
    // std::vector<GameObject> gameObjects_;

    void startLoop() const;

public:
    Engine(int width, int height, const char *title);

    void createObject();

    //void deleteObject();
};
