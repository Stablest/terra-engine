#pragma once
#include <string>
#include "core/math/vector2.hpp"
#include "core/math/vector3.hpp"
#include "core/renderer/data/renderer_texture_2d.hpp"
#include "core/shader/shader_program.hpp"

struct Font;

using Component = unsigned int;
using ComponentType = unsigned int;

constexpr std::size_t MAX_COMPONENTS = 32;

inline ComponentType nextComponentType = 0;

template <typename T>
ComponentType getComponentType() {
    static ComponentType typeId = nextComponentType++;
    return typeId;
}

struct Transform {
    Vector3 position;
    float rotation;
    Vector3 scale;
};

// Decouple OpenGL types
struct Drawable {
    ShaderProgramId shaderProgram = 0;
    int renderLayer = 0;
    bool isTransparent = false;
};

struct Rect {
    Vector2 position = {.0f, .0f};
    Vector2 size = { .0f, .0f };
};

struct Sprite {
    RendererTexture2D *texture = nullptr;
    Rect* source = nullptr;
};

struct Text {
    std::string content;
    Font *font;
};