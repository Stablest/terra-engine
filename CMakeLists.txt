cmake_minimum_required(VERSION 4.0)
project(terra_engine)

set(CMAKE_CXX_STANDARD 20)

# Subdirectories
add_subdirectory(src/drivers/opengl)

add_executable(terra_engine src/main.cpp
        src/core/engine/engine.cpp
        src/core/engine/engine.hpp
        src/core/window/window.cpp
        src/core/window/window.hpp
        src/misc/error/error.cpp
        src/misc/error/error.h
)

target_link_libraries(terra_engine PRIVATE terra_opengl)
target_include_directories(terra_engine PUBLIC include PRIVATE src)