#include "window.hpp"

#include <ostream>
#include <string>
#include "terra_opengl.hpp"
#include "misc/error/error.h"

static void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

Window::Window(const int width, const int height, const char *title) : width(width), height(height), name(title) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow *window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
    if (!window) {
        handleFatalError("Failed to create application window");
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        handleFatalError("Failed to initialize GLAD");
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    handle = window;
    glViewport(0, 0, width, height);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
}

Window::~Window() {
    if (handle) {
        glfwDestroyWindow(handle);
        handle = nullptr;
    }
    glfwTerminate();
}

std::string Window::getName() {
    return this->name;
}

int Window::getWidth() const {
    return this->width;
}

int Window::getHeight() const {
    return this->height;
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(handle);
}

void Window::swapBuffers() const {
    glfwSwapBuffers(handle);
}
