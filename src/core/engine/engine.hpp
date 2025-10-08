#pragma once
#include "core/renderer/renderer.hpp"
#include "core/window/window.hpp"

class IGame;

class Engine {
    Window window_;
    Renderer renderer_;
    IGame *game_;

    void startLoop();

    void queueSprites();

public:
    Engine(int width, int height, const char *title, IGame *game);

    static void registerDefaultComponents();

    static void registerResourceLoaders();
};
