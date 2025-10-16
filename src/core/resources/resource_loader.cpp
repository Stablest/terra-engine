#include "resource_loader.hpp"
#include "misc/error/error.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <fstream>
#include <sstream>
#include "stb/stb_image.h"

bool ImageLoader::canLoad(const std::string &extension) {
    return extension == ".png" || extension == ".jpg" || extension == ".jpeg";
}

std::unique_ptr<Resource> ImageLoader::load(const std::filesystem::path &filePath) {
    int width, height, channels;
    stbi_set_flip_vertically_on_load(false);
    unsigned char *data = stbi_load(filePath.string().c_str(), &width, &height, &channels, 0);
    if (!data) {
        handleWarningError("TEXTURE_LOADER::LOADING_DATA_FAILED");
        return nullptr;
    }
    const size_t bufferSize = static_cast<size_t>(width) * height * channels;
    const std::vector<unsigned char> buffer (data, data + bufferSize);
    auto resource = TextureResource{width, height, channels, filePath.string(), buffer};
    stbi_image_free(data);
    return std::make_unique<TextureResource>(resource);
}


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
