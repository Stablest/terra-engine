#pragma once
#include <filesystem>
#include <memory>
#include <unordered_map>
#include "resource.hpp"
#include "misc/error/error.hpp"

template<typename T>
concept ResourceDerived = std::derived_from<T, Resource>;

class IResourceLoader {
public:
    virtual ~IResourceLoader() = default;

    virtual bool canLoad(const std::string &extension) = 0;

    virtual std::unique_ptr<Resource> load(const std::filesystem::path &filePath) = 0;
};

class ImageLoader final : public IResourceLoader {
public:
    bool canLoad(const std::string &extension) override;

    std::unique_ptr<Resource> load(const std::filesystem::path &filePath) override;
};

class ShaderLoader final : public IResourceLoader {
public:
    bool canLoad(const std::string &extension) override;

    std::unique_ptr<Resource> load(const std::filesystem::path &filePath) override;
};

class ResourceManager {
    std::vector<std::unique_ptr<IResourceLoader> > loaders_ = {};
    std::unordered_map<std::filesystem::path, std::unique_ptr<Resource> > resources_ = {};

    ResourceManager() = default;

public:
    ResourceManager(const ResourceManager &) = delete;

    ResourceManager &operator=(const ResourceManager &) = delete;

    ResourceManager(ResourceManager &&) = delete;

    ResourceManager &operator=(ResourceManager &&) = delete;

    static ResourceManager &getInstance();

    void addLoader(std::unique_ptr<IResourceLoader> _loader);

    template<ResourceDerived T>
    T *load(const std::filesystem::path &path) {
        const std::string extension = path.extension().string();
        for (const auto &loader: loaders_) {
            if (loader->canLoad(extension)) {
                auto resourcePointer = loader->load(path);
                if (resourcePointer == nullptr) {
                    handleWarningError("RESOURCE::LOAD_FAILED", path.string().c_str());
                    return nullptr;
                }
                const auto &stored = resources_[path] = std::move(resourcePointer);
                T *resource = static_cast<T *>(stored.get());
                return resource;
            }
        }
        return nullptr;
    }

    template<ResourceDerived T>
    std::unique_ptr<T> unmanagedLoad(const std::filesystem::path &path) {
        const std::string extension = path.extension().string();
        for (const auto &loader: loaders_) {
            if (loader->canLoad(extension)) {
                auto resourcePointer = loader->load(path);
                if (resourcePointer == nullptr) {
                    handleWarningError("RESOURCE::LOAD_FAILED", path.string().c_str());
                    return nullptr;
                }
                return std::unique_ptr<T>(static_cast<T *>(resourcePointer.release()));
            }
        }
        return nullptr;
    }

    void unload(const std::filesystem::path &path);

};
