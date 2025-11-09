#include "input.hpp"
#include "input_action.hpp"

Input::Input(Window &window) : window_(window) {
    window_.setKeyCallback([this](const Key key, const KeyState state, const int mods) {
        onKeyChanged(key, state, mods);
    });
}

void Input::onKeyChanged(const Key key, const KeyState state, int mods) {
    const int intKey = static_cast<int>(key);
    if (state == KeyState::RELEASED) {
        releasedState_.set(intKey);
        stickyState_.set(intKey, false);
        return;
    }
    if (state == KeyState::PRESSED) {
        pressedState_.set(intKey);
        stickyState_.set(intKey);
    }
}

void Input::resetState() {
    releasedState_.reset();
    pressedState_.reset();
}

void Input::registerAction(const std::string_view name, const InputAction action) {
    actions_[name] = action;
}

bool Input::isActionPressed(const std::string_view name) const {
    if (const auto it = actions_.find(name); actions_.end() != it) {
        const auto [key, modifier] = it->second;
        return pressedState_.test(static_cast<int>(key));
    }
    return false;
}

bool Input::isActionReleased(const std::string_view name) {
    if (const auto it = actions_.find(name); actions_.end() != it) {
        const auto [key, modifier] = it->second;
        return releasedState_.test(static_cast<int>(key));
    }
    return false;
}

bool Input::isAction(const std::string_view name) {
    if (const auto it = actions_.find(name); actions_.end() != it) {
        const auto [key, modifier] = it->second;
        return stickyState_.test(static_cast<int>(key));
    }
    return false;
}
