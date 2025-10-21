#include "object.hpp"

std::string_view Object::getClass() const {
    return "Object";
}

bool Object::isClass(const std::string_view name) const {
    return name == getClass();
}
