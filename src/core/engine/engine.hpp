#pragma once
#include <string>

class Renderer;
class Window;
class Input;
class IGame;

class Engine {
    Window* window_;
    Renderer* renderer_;
    Input* input_;
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

    [[nodiscard]] Input *getInput() const;

    static void registerDefaultComponents();

    static void registerResourceLoaders();

    static Engine& getInstance();
};
