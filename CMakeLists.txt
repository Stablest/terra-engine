cmake_minimum_required(VERSION 4.0)
project(terra_engine)

set(CMAKE_CXX_STANDARD 20)

# Subdirectories
add_subdirectory(drivers/opengl)
add_subdirectory(src/core/shader/resources)

add_executable(terra_engine src/main.cpp
        src/core/engine/engine.cpp
        src/core/engine/engine.hpp
        src/core/window/window.cpp
        src/core/window/window.hpp
        src/core/shader/shader_program.cpp
        src/core/shader/shader_program.hpp
        src/misc/error/error.cpp
        src/misc/error/error.h
        src/core/shader/resources/default_shaders.h
)

target_link_libraries(terra_engine PRIVATE terra_opengl)
target_include_directories(terra_engine PUBLIC include PRIVATE src drivers/opengl)
target_sources(terra_engine PRIVATE ${GENERATED_DEFAULT_SHADERS_CPP})