#include "resource_manager.hpp"

ResourceManager &ResourceManager::getInstance() {
    static ResourceManager resourceManager;
    return resourceManager;
}

void ResourceManager::addLoader(std::unique_ptr<IResourceLoader> _loader) {
    loaders_.push_back(std::move(_loader));
}

void ResourceManager::unload(const std::filesystem::path &path) {
    resources_.erase(path);
}
