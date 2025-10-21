#pragma once
#include <string>
#include "object_type.hpp"

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
        return type_name<T>() == "Object";
    }

    template<typename T>
    T *cast() {
        if (isClass(T::getClassStatic())) {
            return static_cast<T *>(this);
        }
        return nullptr;
    }

    template<typename T>
    T *cast() const {
        if (isClass(T::getClassStatic())) {
            return static_cast<T *>(this);
        }
        return nullptr;
    }
};
