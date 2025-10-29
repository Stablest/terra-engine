#include "shader_program.hpp"
#include <iostream>
#include "misc/error/error.hpp"
#include <string>

ShaderProgram::ShaderProgram(const ShaderProgramId id)
    : id_(id) {
}

void ShaderProgram::use() const {
    glUseProgram(id_);
}

void ShaderProgram::setMatrix4(const std::string &name, const float *value) const {
    glUniformMatrix4fv(glGetUniformLocation(id_, name.c_str()), 1, GL_FALSE, value);
}

void ShaderProgram::setInt(const std::string &name, const int value) const {
    glUniform1i(glGetUniformLocation(id_, name.c_str()), value);
}

ShaderProgramId ShaderProgram::getId() const {
    return id_;
}

std::optional<ShaderProgram> ShaderProgram::createProgram(const ShaderId vertexShader,
                                                          const ShaderId fragmentShader,
                                                          const ShaderId geometryShader, const bool isFatal) {
    const ShaderProgramId id = glCreateProgram();
    if (id == 0) {
        if (isFatal) {
            handleFatalError("Couldn't create shader program");
        } else {
            handleWarningError("Couldn't create shader program");
            return std::nullopt;
        }
    }
    glAttachShader(id, vertexShader);
    glAttachShader(id, fragmentShader);
    if (geometryShader != 0) {
        glAttachShader(id, geometryShader);
    }
    glLinkProgram(id);
    GLint linkSuccess = 0;
    glGetProgramiv(id, GL_LINK_STATUS, &linkSuccess);
    if (!linkSuccess) {
        glDeleteProgram(id);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        if (geometryShader != 0) {
            glDeleteShader(geometryShader);
        }
        if (isFatal) {
            handleFatalError("Couldn't link shader program");
        } else {
            handleWarningError("Couldn't link shader program");
            return std::nullopt;
        }
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    if (geometryShader != 0) {
        glDeleteShader(geometryShader);
    }
    return ShaderProgram(id);
}

std::optional<ShaderProgram> ShaderProgram::createCustomProgram(const ShaderId vertexShader,
                                                                const ShaderId fragmentShader,
                                                                const ShaderId geometryShader) {
    return createProgram(vertexShader, fragmentShader, geometryShader, false);
}

ShaderProgram ShaderProgram::createDefaultProgram(const ShaderId vertexShader, const ShaderId fragmentShader,
                                                  const ShaderId geometryShader) {
    return createProgram(vertexShader, fragmentShader, geometryShader, true).value();
}


ShaderId ShaderProgram::compileShader(const GLenum type, const char *content, const bool isFatal) {
    const ShaderId id = glCreateShader(type);
    glShaderSource(id, 1, &content, nullptr);
    glCompileShader(id);
    GLint status;
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);
    if (!status) {
        GLint logLength = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLength);
        std::string errorLog;
        errorLog.resize(logLength);
        if (logLength > 0) {
            glGetShaderInfoLog(id, logLength, &logLength, errorLog.data());
        }
        glDeleteShader(id);
        const std::string typeName = (type == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT";
        const std::string title = "SHADER::" + typeName  + "::COMPILATION_FAILED";
        if (isFatal) {
            handleFatalError(title.c_str(), errorLog.c_str());
        } else {
            handleWarningError(title.c_str(), errorLog.c_str());
        }
    }
    return id;
}

ShaderId ShaderProgram::compileCustomShader(const GLenum type, const char *content) {
    return compileShader(type, content, false);
}

ShaderId ShaderProgram::compileDefaultShader(const GLenum type, const char *content) {
    return compileShader(type, content, true);
}
