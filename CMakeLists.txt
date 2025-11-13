cmake_minimum_required(VERSION 4.0)
project(terra_engine)

set(CMAKE_CXX_STANDARD 20)

# Subdirectories
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/drivers/opengl)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src/core/renderer/sprite/shaders)

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
        src/core/resources/resource.cpp
        src/core/resources/resource.hpp
        src/core/object/object.cpp
        src/core/object/object.hpp
        src/core/object/class.hpp
        src/core/resources/texture/texture_loader.cpp
        src/core/resources/texture/texture_loader.hpp
        src/core/resources/texture/texture_resource.cpp
        src/core/resources/texture/texture_resource.hpp
        src/core/resources/shader/shader_loader.cpp
        src/core/resources/shader/shader_loader.hpp
        src/core/resources/shader/shader_resource.cpp
        src/core/resources/shader/shader_resource.hpp
        src/core/resources/resource_manager.cpp
        src/core/resources/resource_manager.hpp
        src/core/math/vector2.hpp
        src/core/math/matrix4.hpp
        src/core/math/vector3.hpp
        src/core/math/vector4.hpp
        src/core/input/input.cpp
        src/core/input/input.hpp
        src/core/input/input_action.cpp
        src/core/input/input_action.hpp
        src/core/window/key.hpp
        src/misc/dense_array/packed_array.hpp
)

add_dependencies(terra_engine GenerateShaders)
target_link_libraries(terra_engine PUBLIC terra_opengl PUBLIC stb_image)
target_include_directories(terra_engine PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
        ${CMAKE_CURRENT_LIST_DIR}/src
        ${CMAKE_CURRENT_LIST_DIR}/drivers/opengl
        ${CMAKE_CURRENT_LIST_DIR}/third-parties/header-only
)
target_sources(terra_engine PRIVATE ${GENERATED_DEFAULT_SHADERS_CPP})

add_library(stb_image STATIC src/misc/stb_image.cpp)
target_include_directories(stb_image PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/third-parties
)

