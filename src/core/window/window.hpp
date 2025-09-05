#pragma once

#include <string>

struct GLFWwindow;

class Window {
    GLFWwindow *handle_;
    int width_, height_;
    std::string name_;

public:
    explicit Window(int width, int height, const char *title);

    ~Window();

    [[nodiscard]] int getWidth() const;

    [[nodiscard]] int getHeight() const;

    std::string getName();

    [[nodiscard]] bool shouldClose() const;

    void swapBuffers() const;
};
