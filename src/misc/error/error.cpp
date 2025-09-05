#ifdef _WIN32
#include <windows.h>
#endif

#include "error.h"
#include <iostream>
#include "terra-opengl.hpp"

namespace {
    void fatal_exit() {
#ifdef NDEBUG
        std::exit(EXIT_FAILURE);
#else
#if defined(_MSC_VER)
#elif defined(__GNUC__) || defined(__clang__)
        __builtin_trap();
#else
        std::abort();
#endif
#endif
    }

    void log(const char *message) {
#ifndef NDEBUG
        std::cerr << message << std::endl;
#endif
    }

    // TODO Create popup to Linux
    void show_popup(const char *message) {
#ifdef _WIN32
        MessageBoxA(nullptr, message, "Fatal Error", MB_OK | MB_ICONERROR);
#endif
    }
}

void handleFatalError(const char *message) {
    log(message);
    glfwTerminate();
    show_popup(message);
    fatal_exit();
}

void handleWarningError(const char *message) {
    log(message);
}
