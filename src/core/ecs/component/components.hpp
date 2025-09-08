#pragma once
#include <string>

#include "core/resources/texture.hpp"
#include "core/shader/shader_program.hpp"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

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
    glm::vec3 position;
    float rotation;
    glm::vec3 scale;
};

// Decouple OpenGL types
struct Drawable {
    GLuint shaderProgram = 0;
    int renderLayer = 0;
    bool isTransparent = false;
};

// struct Texture {
//     unsigned int id = 0;
//     unsigned int channels = 4;
//     glm::vec2 size = glm::vec2(.0f, .0f);
// };

struct Rect {
    glm::vec2 position = {.0f, .0f};
    glm::vec2 size = { .0f, .0f };
};

struct Sprite {
    Texture2D *texture = nullptr;
    Rect* source = nullptr;
};

struct Text {
    std::string content;
    Font *font;
};