cmake_minimum_required(VERSION 4.0)
project(terra_engine)

set(CMAKE_CXX_STANDARD 20)

# Subdirectories
add_subdirectory(third-parties/glfw-3.4)

# Libraries
add_library(glad STATIC third-parties/glad/src/glad.c)
target_include_directories(glad PUBLIC third-parties/glad/include)

add_executable(terra_engine src/main.cpp)

target_link_libraries(terra_engine PRIVATE glfw)
target_include_directories(terra_engine PRIVATE include)