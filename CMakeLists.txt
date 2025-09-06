cmake_minimum_required(VERSION 4.0)
project(terra_engine)

set(CMAKE_CXX_STANDARD 20)

# Subdirectories
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/drivers/opengl)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src/core/shader/resources)

add_library(terra_engine
        src/core/engine/engine.cpp
        src/core/window/window.cpp
        src/core/shader/shader_program.cpp
        src/misc/error/error.cpp
)

target_link_libraries(terra_engine PUBLIC terra_opengl)
target_include_directories(terra_engine PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include ${CMAKE_CURRENT_LIST_DIR}/src ${CMAKE_CURRENT_LIST_DIR}/drivers/opengl)
target_sources(terra_engine PRIVATE ${GENERATED_DEFAULT_SHADERS_CPP})