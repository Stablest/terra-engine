#pragma once
#include "core/resources/resource_loader.hpp"

class ShaderLoader final : public IResourceLoader {
public:
    bool canLoad(const std::string &extension) override;

    std::unique_ptr<Resource> load(const std::filesystem::path &filePath) override;
};
