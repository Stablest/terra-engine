#pragma once
#include <memory>
#include "resource.hpp"

template<typename T>
class IResourceLoader {
public:
    virtual ~IResourceLoader() = default;

    virtual bool canLoad(const std::string &extension) = 0;

    virtual std::shared_ptr<T> load(const std::string &filePath) = 0;
};

class ImageLoader final : public IResourceLoader<TextureResource> {
public:
    bool canLoad(const std::string &extension) override;

    std::shared_ptr<TextureResource> load(const std::string &filePath) override;
};

class ShaderLoader final : public IResourceLoader<ShaderResource> {
public:
    bool canLoad(const std::string &extension) override;

    std::shared_ptr<ShaderResource> load(const std::string &filePath) override;
};
