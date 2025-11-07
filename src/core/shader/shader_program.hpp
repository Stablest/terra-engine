#pragma once
#include <optional>
#include <string>
#include "terra_opengl.hpp"
#include "core/math/vector4.hpp"

using ShaderProgramId = unsigned int;

using ShaderId = unsigned int;

class ShaderProgram {
    ShaderProgramId id_;

    static std::optional<ShaderProgram> createProgram(ShaderId vertexShader, ShaderId fragmentShader,
                                                      ShaderId geometryShader = 0, bool isFatal = false);

    static ShaderId compileShader(GLenum type, const char *content, bool isFatal);

public:
    explicit ShaderProgram(ShaderProgramId id);

    void use() const;

    void setMatrix4(const std::string &name, const float* value) const;

    void setVec(const std::string &name, Vector4 vec) const;

    void setInt(const std::string &name, int value) const;

    [[nodiscard]] ShaderProgramId getId() const;

    static std::optional<ShaderProgram> createCustomProgram(ShaderId vertexShader, ShaderId fragmentShader,
                                                            ShaderId geometryShader = 0);

    static ShaderProgram createDefaultProgram(ShaderId vertexShader, ShaderId fragmentShader, ShaderId geometryShader = 0);

    static ShaderId compileCustomShader(GLenum type, const char *content);

    static ShaderId compileDefaultShader(GLenum type, const char *content);
};
