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
        src/core/renderer/renderer.cpp
        src/core/ecs/component/components.hpp
        src/core/ecs/component/component_manager.cpp
        src/core/ecs/component/component-storage.hpp
        src/core/ecs/entity-manager.cpp
        src/core/ecs/archetypes.hpp
        src/core/renderer/data/renderer_texture_2d.cpp
        src/core/renderer/sprite/sprite_render_queue.cpp
        src/core/renderer/sprite/sprite_renderer.cpp
        src/core/resources/resource_loader.cpp
        src/core/resources/resource.cpp
        src/core/resources/resource.hpp
)

add_dependencies(terra_engine GenerateShaders)
target_link_libraries(terra_engine PUBLIC terra_opengl)
target_include_directories(terra_engine PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
        ${CMAKE_CURRENT_LIST_DIR}/src
        ${CMAKE_CURRENT_LIST_DIR}/drivers/opengl
        ${CMAKE_CURRENT_LIST_DIR}/third-parties/header-only
)
target_sources(terra_engine PRIVATE ${GENERATED_DEFAULT_SHADERS_CPP})

