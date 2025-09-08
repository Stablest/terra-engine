#include "shader_program.hpp"
#include <iostream>
#include "misc/error/error.hpp"
#include <string>
#include <vector>

ShaderProgram::ShaderProgram(const GLuint id)
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

GLuint ShaderProgram::getId() const {
    return id_;
}

std::optional<ShaderProgram> ShaderProgram::createProgram(const unsigned int vertexShader,
                                                          const unsigned int fragmentShader,
                                                          const unsigned int geometryShader, const bool isFatal) {
    const GLuint id = glCreateProgram();
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

std::optional<ShaderProgram> ShaderProgram::createCustomProgram(const unsigned int vertexShader,
                                                                const unsigned int fragmentShader,
                                                                const unsigned int geometryShader) {
    return createProgram(vertexShader, fragmentShader, geometryShader, false);
}

ShaderProgram ShaderProgram::createDefaultProgram(const unsigned int vertexShader, const unsigned int fragmentShader,
                                                  const unsigned int geometryShader) {
    return createProgram(vertexShader, fragmentShader, geometryShader, true).value();
}


GLuint ShaderProgram::createShader(const GLenum type, const char *content, const bool isFatal) {
    const GLuint id = glCreateShader(type);
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

GLuint ShaderProgram::createCustomShader(const GLenum type, const char *content) {
    return createShader(type, content, false);
}

GLuint ShaderProgram::createDefaultShader(const GLenum type, const char *content) {
    return createShader(type, content, true);
}
