#pragma once

#include <functional>
#include <string>
#include "key.hpp"
#include "terra_opengl.hpp"

struct GLFWwindow;

static constexpr std::array<Key, 349> createKeyLookUpTable() {
    std::array<Key, GLFW_KEY_LAST + 1> table{};
    table.fill(Key::NONE);
    table[GLFW_KEY_A] = Key::A;
    table[GLFW_KEY_B] = Key::B;
    table[GLFW_KEY_C] = Key::C;
    table[GLFW_KEY_D] = Key::D;
    table[GLFW_KEY_E] = Key::E;
    table[GLFW_KEY_F] = Key::F;
    table[GLFW_KEY_G] = Key::G;
    table[GLFW_KEY_H] = Key::H;
    table[GLFW_KEY_I] = Key::I;
    table[GLFW_KEY_J] = Key::J;
    table[GLFW_KEY_K] = Key::K;
    table[GLFW_KEY_L] = Key::L;
    table[GLFW_KEY_M] = Key::M;
    table[GLFW_KEY_N] = Key::N;
    table[GLFW_KEY_O] = Key::O;
    table[GLFW_KEY_P] = Key::P;
    table[GLFW_KEY_Q] = Key::Q;
    table[GLFW_KEY_R] = Key::R;
    table[GLFW_KEY_S] = Key::S;
    table[GLFW_KEY_T] = Key::T;
    table[GLFW_KEY_U] = Key::U;
    table[GLFW_KEY_V] = Key::V;
    table[GLFW_KEY_W] = Key::W;
    table[GLFW_KEY_X] = Key::X;
    table[GLFW_KEY_Y] = Key::Y;
    table[GLFW_KEY_Z] = Key::Z;
    table[GLFW_KEY_0] = Key::NUM_0;
    table[GLFW_KEY_1] = Key::NUM_1;
    table[GLFW_KEY_2] = Key::NUM_2;
    table[GLFW_KEY_3] = Key::NUM_3;
    table[GLFW_KEY_4] = Key::NUM_4;
    table[GLFW_KEY_5] = Key::NUM_5;
    table[GLFW_KEY_6] = Key::NUM_6;
    table[GLFW_KEY_7] = Key::NUM_7;
    table[GLFW_KEY_8] = Key::NUM_8;
    table[GLFW_KEY_9] = Key::NUM_9;
    table[GLFW_KEY_SPACE] = Key::SPACE;
    table[GLFW_KEY_ENTER] = Key::ENTER;
    table[GLFW_KEY_LEFT_SHIFT] = Key::LEFT_SHIFT;
    table[GLFW_KEY_RIGHT_SHIFT] = Key::RIGHT_SHIFT;
    table[GLFW_KEY_LEFT_CONTROL] = Key::LEFT_CONTROL;
    table[GLFW_KEY_RIGHT_CONTROL] = Key::RIGHT_CONTROL;
    table[GLFW_KEY_LEFT_ALT] = Key::LEFT_ALT;
    table[GLFW_KEY_RIGHT_ALT] = Key::RIGHT_ALT;
    table[GLFW_KEY_UP] = Key::ARROW_UP;
    table[GLFW_KEY_DOWN] = Key::ARROW_DOWN;
    table[GLFW_KEY_LEFT] = Key::ARROW_LEFT;
    table[GLFW_KEY_RIGHT] = Key::ARROW_RIGHT;
    table[GLFW_KEY_ESCAPE] = Key::ESCAPE;
    return table;
}

static constexpr auto KEY_TABLE = createKeyLookUpTable();

class Window {
    GLFWwindow *handle_;
    int width_, height_;
    std::string name_;

    std::function<void(Key, KeyState, int)> onKeyHandled;


    [[nodiscard]] static constexpr Key translateKeyToEngineKey(int key);

    [[nodiscard]] static constexpr KeyState translateStateToEngineState(int state);

public:
    explicit Window(int width, int height, const char *title);

    ~Window();

    [[nodiscard]] int getWidth() const;

    [[nodiscard]] int getHeight() const;

    std::string getName();

    [[nodiscard]] bool shouldClose() const;

    void setKeyCallback(std::function<void(Key, KeyState, int)> &&callback);

    [[nodiscard]] KeyState getKeyState(Key key) const;

    void pollEvents() const;

    void swapBuffers() const;
};
