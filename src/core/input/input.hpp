#pragma once
#include <bitset>
#include <unordered_map>
#include "input_action.hpp"
#include "core/window/window.hpp"

constexpr int MAX_KEY_INDEXES = 512;

class Input {
    Window &window_;
    std::bitset<MAX_KEY_INDEXES> pressedState_;
    std::bitset<MAX_KEY_INDEXES> releasedState_;
    std::bitset<MAX_KEY_INDEXES> stickyState_;
    std::unordered_map<std::string_view, InputAction> actions_;

    friend class Engine;

    void onKeyChanged(Key key, KeyState state, int mods);

    void resetState();

public:
    explicit Input(Window &window);

    void registerAction(std::string_view name, InputAction action);

    [[nodiscard]] bool isActionPressed(std::string_view inputAction) const;

    [[nodiscard]] bool isActionReleased(std::string_view name);

    [[nodiscard]] bool isAction(std::string_view name);
};
