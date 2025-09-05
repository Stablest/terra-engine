#include "shader_program.hpp"
#include "misc/error/error.h"
#include <string>

ShaderProgram::ShaderProgram(const GLuint id, const unsigned int vertexShader, const unsigned int fragmentShader,
                             const unsigned int geometryShader)
    : id_(id), vertexShader_(vertexShader), fragmentShader_(fragmentShader), geometryShader_(geometryShader) {
}

ShaderProgram::~ShaderProgram() {
    glDeleteShader(vertexShader_);
    glDeleteShader(fragmentShader_);
    if (geometryShader_ != 0) {
        glDeleteShader(geometryShader_);
    }
    glDeleteProgram(id_);
}

void ShaderProgram::use() const {
    glUseProgram(id_);
}

std::optional<ShaderProgram> ShaderProgram::createProgram(const unsigned int vertexShader, const unsigned int fragmentShader,
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
    if (linkSuccess == GL_FALSE) {
        glDeleteProgram(id);
        if (isFatal) {
            handleFatalError("Couldn't link shader program");
        } else {
            handleWarningError("Couldn't link shader program");
            return std::nullopt;
        }
    }
    return ShaderProgram(id, vertexShader, fragmentShader, geometryShader);
}

std::optional<ShaderProgram> ShaderProgram::createCustomProgram(const unsigned int vertexShader, const unsigned int fragmentShader,
                                                const unsigned int geometryShader) {
    return createProgram(vertexShader, fragmentShader, geometryShader, false);
}

ShaderProgram ShaderProgram::createDefaultProgram(const unsigned int vertexShader, const unsigned int fragmentShader,
                                                 const unsigned int geometryShader) {
    return createProgram(vertexShader, fragmentShader, geometryShader, true).value();
}


GLuint ShaderProgram::createShader(const GLenum type, const char *file, const bool isFatal) {
    const GLuint id = glCreateShader(type);
    glShaderSource(id, 1, reinterpret_cast<const GLchar * const *>(&file), nullptr);
    glCompileShader(id);
    GLint status;
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        glGetShaderInfoLog(id, sizeof(GLchar), nullptr, nullptr);
        if (isFatal) {
            glDeleteShader(id);
            handleFatalError("Error compiling shader");
        } else {
            glDeleteShader(id);
            handleWarningError("Error compiling shader");
        }
    }
    return id;
}

GLuint ShaderProgram::createCustomShader(const GLenum type, const char *file) {
    return createShader(type, file, false);
}

GLuint ShaderProgram::createDefaultShader(const GLenum type, const char *file) {
    return createShader(type, file, true);
}
