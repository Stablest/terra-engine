#pragma once
#include <string>
#include "class.hpp"

class Object {
public:
    virtual ~Object() = default;

    static constexpr std::string_view getClassStatic() {
        return "Object";
    }

    [[nodiscard]] virtual std::string_view getClass() const;

    [[nodiscard]] virtual bool isClass(std::string_view name) const;

    template<typename T>
    static bool isClass() {
        return getTypeName<T>() == "Object";
    }

    template<typename T>
    [[nodiscard]] T *cast() {
        if (isClass(T::getClassStatic())) {
            return static_cast<T *>(this);
        }
        return nullptr;
    }

    template<typename T>
    [[nodiscard]] const T *cast() const {
        if (isClass(T::getClassStatic())) {
            return static_cast<const T *>(this);
        }
        return nullptr;
    }
};
