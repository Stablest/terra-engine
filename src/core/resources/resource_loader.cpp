#include "resource_loader.hpp"

#include "misc/error/error.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

bool ImageLoader::canLoad(const std::string &extension) {
    return extension == ".png" || extension == ".jpg" || extension == ".jpeg";
}

std::unique_ptr<TextureResource> ImageLoader::load(const std::string &filePath) {
    int width, height, channels;
    stbi_set_flip_vertically_on_load(false);
    unsigned char *data = stbi_load(filePath.c_str(), &width, &height, &channels, 0);
    if (!data) {
        handleWarningError("TEXTURE_LOADER::LOADING_DATA_FAILED");
        return nullptr;
    }
    const size_t bufferSize = static_cast<size_t>(width) * height * channels;
    const std::vector buffer(reinterpret_cast<std::byte *>(data),
                             reinterpret_cast<std::byte *>(data) + bufferSize);
    auto resource = TextureResource{width, height, channels, filePath, buffer};
    stbi_image_free(data);
    return std::make_unique<TextureResource>(resource);
}


bool ShaderLoader::canLoad(const std::string &extension) {
    return extension == ".glsl";
}

std::unique_ptr<ShaderResource> ShaderLoader::load(const std::string &filePath) {
    return nullptr;
}
