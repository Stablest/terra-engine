#pragma once
#include <optional>
#include <string>
#include "terra_opengl.hpp"

using Shader = unsigned int;

class ShaderProgram {
    GLuint id_;

    static std::optional<ShaderProgram> createProgram(GLuint vertexShader, GLuint fragmentShader,
                                                      GLuint geometryShader = 0, bool isFatal = false);

    static GLuint createShader(GLenum type, const char *content, bool isFatal);

public:
    explicit ShaderProgram(GLuint id);

    void use() const;

    void setMatrix4(const std::string &name, const float* value) const;

    void setInt(const std::string &name, int value) const;

    [[nodiscard]] GLuint getId() const;

    static std::optional<ShaderProgram> createCustomProgram(GLuint vertexShader, GLuint fragmentShader,
                                                            GLuint geometryShader = 0);

    static ShaderProgram createDefaultProgram(GLuint vertexShader, GLuint fragmentShader, GLuint geometryShader = 0);

    static GLuint createCustomShader(GLenum type, const char *content);

    static GLuint createDefaultShader(GLenum type, const char *content);
};
