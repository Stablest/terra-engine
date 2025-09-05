#pragma once

#include <optional>
#include "terra_opengl.hpp"

class ShaderProgram {
    GLuint id_ = 0;
    GLuint vertexShader_ = 0;
    GLuint fragmentShader_ = 0;
    GLuint geometryShader_ = 0;

    static std::optional<ShaderProgram> createProgram(GLuint vertexShader, GLuint fragmentShader, GLuint geometryShader = 0, bool isFatal = false);

    static GLuint createShader(GLenum type, const char *file, bool isFatal);

public:
    ShaderProgram(GLuint id, GLuint vertexShader, GLuint fragmentShader, GLuint geometryShader = 0);

    ~ShaderProgram();

    void use() const;

    static std::optional<ShaderProgram> createCustomProgram(GLuint vertexShader, GLuint fragmentShader, GLuint geometryShader = 0);

    static ShaderProgram createDefaultProgram(GLuint vertexShader, GLuint fragmentShader, GLuint geometryShader = 0);

    static GLuint createCustomShader(GLenum type, const char *file);

    static GLuint createDefaultShader(GLenum type, const char *file);
};
