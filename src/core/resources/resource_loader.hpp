#pragma once
#include <filesystem>
#include <memory>
#include "resource.hpp"

template<typename T>
concept ResourceDerived = std::derived_from<T, Resource>;

class IResourceLoader {
public:
    virtual ~IResourceLoader() = default;

    virtual bool canLoad(const std::string &extension) = 0;

    virtual std::unique_ptr<Resource> load(const std::filesystem::path &filePath) = 0;

    virtual std::unique_ptr<Resource> getFallback() = 0;
};
