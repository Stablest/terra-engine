#pragma once
#include <memory>
#include <unordered_map>
#include <vector>
#include "resource_loader.hpp"
#include "misc/error/error.hpp"

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
        if (const auto it = resources_.find(path); it != resources_.end()) {
            const auto& resource = it->second;
            return resource->template cast<T>();
        }
        for (const auto &loader: loaders_) {
            if (loader->canLoad(extension)) {
                auto resourcePointer = loader->load(path);
                if (resourcePointer == nullptr) {
                    handleWarningError("RESOURCE::LOAD_FAILED", path.string().c_str());
                    return nullptr;
                }
                const auto &stored = resources_[path] = std::move(resourcePointer);
                T *resource = stored->template cast<T>();
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
                T *resource = resourcePointer.release()->template cast<T>();
                return std::unique_ptr<T>(resource);
            }
        }
        return nullptr;
    }

    void unload(const std::filesystem::path &path);
};
