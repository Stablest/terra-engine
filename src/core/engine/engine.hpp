#pragma once

#include "../window/window.hpp"

class Engine {
    Window window;

    void startLoop() const;

public:
    Engine(int width, int height, const char *title);
};
