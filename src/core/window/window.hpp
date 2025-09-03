#ifndef TERRA_ENGINE_WINDOW_HPP
#define TERRA_ENGINE_WINDOW_HPP

#endif //TERRA_ENGINE_WINDOW_HPP

#include <string>

struct GLFWwindow;

class Window {
    GLFWwindow *handle;
    int width, height;
    std::string name;

public:
    explicit Window(int width, int height, const char *title);

    ~Window();

    [[nodiscard]] int getWidth() const;

    [[nodiscard]] int getHeight() const;

    std::string getName();

    [[nodiscard]] bool shouldClose() const;

    void swapBuffers() const;
};
