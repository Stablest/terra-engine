#include "shader_resource.hpp"

ShaderResource::ShaderResource(std::filesystem::path path, std::string data)
    : Class(std::move(path)), data_(std::move(data)) {
}
