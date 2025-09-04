#ifndef TERRA_ENGINE_ENGINE_HPP
#define TERRA_ENGINE_ENGINE_HPP
#include "../window/window.hpp"

#endif //TERRA_ENGINE_ENGINE_HPP


class Engine {
    Window window;

    void start_loop() const;

public:
    Engine(int width, int height, const char *title);
};
