#include "shader_loader.hpp"
#include <fstream>
#include "shader_resource.hpp"
#include "misc/error/error.hpp"

bool ShaderLoader::canLoad(const std::string &extension) {
    return extension == ".glsl";
}

std::unique_ptr<Resource> ShaderLoader::load(const std::filesystem::path &filePath) {
    std::ifstream stream;
    std::string shaderSource;
    stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        stream.open(filePath);
        std::stringstream buffer;
        buffer << stream.rdbuf();
        shaderSource = buffer.str();
    } catch (std::ifstream::failure &e) {
        handleWarningError("SHADER_RESOURCE_LOADER::LOADING_DATA_FAILED", e.what());
        return nullptr;
    }
    return std::make_unique<ShaderResource>(filePath.string(), std::move(shaderSource));
}
