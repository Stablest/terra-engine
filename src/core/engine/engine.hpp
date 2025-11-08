#pragma once
#include "core/renderer/renderer.hpp"
#include "core/window/window.hpp"

class IGame;

class Engine {
    Window* window_;
    Renderer* renderer_;
    IGame *game_;

    void startLoop() const;

    void queueSprites() const;

    Engine() = default;

public:
    Engine(const Engine &) = delete;

    Engine &operator=(const Engine &) = delete;

    Engine(Engine &&) = delete;

    Engine &operator=(Engine &&) = delete;

    void init(int width, int height, std::string&& title, IGame* game);

    static void registerDefaultComponents();

    static void registerResourceLoaders();

    static Engine& getInstance();
};
