#pragma once
#include "core/object/class.hpp"
#include "core/resources/resource.hpp"

class ShaderResource final : public Class<ShaderResource, Resource> {
    std::string data_;

public:
    explicit ShaderResource(std::filesystem::path path, std::string data);
};
