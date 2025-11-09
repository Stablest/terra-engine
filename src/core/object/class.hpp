#pragma once
#include <string_view>

template<typename T>
constexpr std::string_view type_name() {
#if defined(__clang__)
    constexpr std::string_view prefix = "std::string_view type_name() [T = ";
    constexpr std::string_view function = __PRETTY_FUNCTION__;
#elif defined(__GNUC__)
    constexpr std::string_view prefix = "constexpr std::string_view type_name() [with T = ";
    constexpr std::string_view function = __PRETTY_FUNCTION__;
#elif defined(_MSC_VER)
    constexpr std::string_view prefix = "type_name<";
    constexpr std::string_view suffix = ">(void)";
    constexpr std::string_view function = __FUNCSIG__;
#else
#   error Unsupported compiler
#endif
    constexpr size_t start = function.find(prefix) + prefix.size();
#if defined(_MSC_VER)
    const size_t end = function.rfind(suffix);
    return function.substr(start, end - start);
#else
    constexpr size_t semicolon = function.find(';', start);
    constexpr size_t end = (semicolon == std::string_view::npos)
                               ? function.find(']', start)
                               : semicolon;
    return function.substr(start, end - start);
#endif
}

template<typename Derived, typename Base>
class Class : public Base {
public:
    using Base::Base;

    static constexpr std::string_view getClassStatic() {
        return type_name<Derived>();
    }

    [[nodiscard]] std::string_view getClass() const override {
        return type_name<Derived>();
    }

    [[nodiscard]] bool isClass(std::string_view name) const override {
        return name == type_name<Derived>() || Base::isClass(name);
    }

    template<typename T>
    [[nodiscard]] bool isClass() const {
        return type_name<T>() == getClass() || Base::template isClass<T>();
    }
};