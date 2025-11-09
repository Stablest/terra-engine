#include "window.hpp"

#include <iostream>
#include <ostream>
#include <string>
#include "misc/error/error.hpp"

static void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

Window::Window(const int width, const int height, const char *title) : width_(width), height_(height), name_(title) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow *glfwWindow = glfwCreateWindow(width, height, name_.c_str(), nullptr, nullptr);
    if (!glfwWindow) {
        handleFatalError("Failed to create application window");
    }
    glfwMakeContextCurrent(glfwWindow);
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        handleFatalError("Failed to initialize GLAD");
    }
    glfwSetFramebufferSizeCallback(glfwWindow, framebuffer_size_callback);
    handle_ = glfwWindow;
    glfwSetWindowUserPointer(handle_, this);
    glfwSetKeyCallback(
        handle_, [](GLFWwindow *window, const int key, const int scanCode, const int action, const int mods) {
            const auto *currentWindow = static_cast<Window *>(glfwGetWindowUserPointer(window));
            const Key engineKey = translateKeyToEngineKey(key);
            const KeyState engineState = translateStateToEngineState(action);
            currentWindow->onKeyHandled(engineKey, engineState, mods);
        });
    glViewport(0, 0, width, height);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
}

Window::~Window() {
    if (handle_) {
        glfwDestroyWindow(handle_);
        handle_ = nullptr;
    }
    glfwTerminate();
}

constexpr Key Window::translateKeyToEngineKey(const int key) {
    if (key < 0 || key > GLFW_KEY_LAST) {
        return Key::NONE;
    }
    return KEY_TABLE[key];
}

constexpr KeyState Window::translateStateToEngineState(const int state) {
    if (state > 3 || state < 0) {
        return KeyState::NONE;
    }
    constexpr std::array<KeyState, 3> states{
        KeyState::RELEASED,
        KeyState::PRESSED,
        KeyState::REPEATED,
    };
    return states[state];
}

std::string Window::getName() {
    return this->name_;
}

int Window::getWidth() const {
    return this->width_;
}

int Window::getHeight() const {
    return this->height_;
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(handle_);
}

void Window::setKeyCallback(std::function<void(Key, KeyState, int)> &&callback) {
    onKeyHandled = callback;
}

// TODO # Fix Key input
KeyState Window::getKeyState(const Key key) const {
    switch (glfwGetKey(handle_, static_cast<int>(key))) {
        case GLFW_PRESS: return KeyState::PRESSED;
        case GLFW_RELEASE: return KeyState::RELEASED;
        case GLFW_REPEAT: return KeyState::REPEATED;
        default: return KeyState::NONE;
    }
}

void Window::pollEvents() const {
    glfwPollEvents();
}

void Window::swapBuffers() const {
    glfwSwapBuffers(handle_);
}
