#pragma once

#include "core/shader/shader_program.hpp"

class RenderQueue;

struct DrawCommand {
    GLuint vao_ = 0;
    GLuint shader_ = 0;
    GLuint texture_ = 0;
    GLenum drawMode_ = GL_TRIANGLES;
    GLsizei vertexCount_ = 0;
    mutable uint64_t sortKey_ = 0;
};

class Renderer {

public:
    void render(RenderQueue& queue);
};
